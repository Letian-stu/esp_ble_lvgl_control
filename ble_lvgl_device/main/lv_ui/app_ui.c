/*
 * @Author: Letian-stu
 * @Date: 2023-05-12 14:55
 * @LastEditors: Letian-stu
 * @LastEditTime: 2023-05-20 10:18
 * @FilePath: /ble_lvgl_device/main/lv_ui/app_ui.c
 * @Description:
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#include "app_ui.h"
#include "ble_hidd_main.h"

#define TAG "ui"

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[DISP_BUF_SIZE];
static lv_color_t buf2[DISP_BUF_SIZE];

lv_group_t *Screen_btn_group;
lv_group_t *back_menu_btn_group;
//主界面
lv_obj_t *ui_Screen;
lv_obj_t *scrool;
lv_obj_t *Screen_btn;
lv_obj_t *Screen_img;
lv_obj_t *Screen_lab;

//每个屏幕
lv_obj_t *ui_Screen_Time;
lv_obj_t *ui_Screen_Daily;
lv_obj_t *ui_Screen_Wifi;
lv_obj_t *ui_Screen_Ble;
lv_obj_t *ui_Screen_Voice;
lv_obj_t *ui_Screen_Clock;
lv_obj_t *ui_Screen_Set;
lv_obj_t *ui_Screen_About;

//返回 菜单
lv_obj_t *ui_Page_back_btn;
lv_obj_t *ui_Page_back_img;
lv_obj_t *ui_Page_menu_btn;
lv_obj_t *ui_Page_menu_img;
lv_obj_t *label;

lv_obj_t *ui_Time;
lv_obj_t *ui_ImageWatchface;
lv_obj_t *ui_ImageArmHour;
lv_obj_t *ui_ImageArmMinute;
lv_obj_t *ui_ImageArmSecond;


static void lv_tick_task(void *arg)
{
    lv_tick_inc(LV_TICK_PERIOD_MS);
}

void ui_screen_change(lv_obj_t *obj, lv_scr_load_anim_t fademode, uint32_t time, uint32_t delay)
{
    lv_scr_load_anim(obj, fademode, time, delay, false);
}

void page_screen_anim(lv_obj_t *obj, int32_t start, int32_t end, uint32_t time, uint32_t delay, lv_anim_exec_xcb_t exec_cb,lv_anim_path_cb_t path_cb)
{
    lv_anim_t a;

    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_values(&a, start, end);
    lv_anim_set_time(&a, time);
    lv_anim_set_delay(&a, delay);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)exec_cb);
    lv_anim_set_path_cb(&a, path_cb);
    lv_anim_start(&a);
}

static void scroll_event_cb(lv_event_t *e)
{
    lv_obj_t *cont = lv_event_get_target(e);
    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a);
    lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2;

    lv_coord_t r = lv_obj_get_height(cont) * 7 / 12; // lv_obj_get_height(cont) * 7 / 10;
    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);
    for (i = 0; i < child_cnt; i++)
    {
        lv_obj_t *child = lv_obj_get_child(cont, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);

        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2;

        lv_coord_t diff_y = child_y_center - cont_y_center;
        diff_y = LV_ABS(diff_y);

        /*Get the x of diff_y on a circle.*/
        lv_coord_t x;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if (diff_y >= r)
        {
            x = r;
        }
        else
        {
            /*Use Pythagoras theorem to get x from radius and y*/
            uint32_t x_sqr = r * r - diff_y * diff_y;
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000); /*Use lvgl's built in sqrt root function*/
            x = r - res.i;
        }

        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_x(child, x + 85, 0);

        /*Use some opacity with larger translations*/
        lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
        lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0);
    }
}

void lv_btn_back_menu_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    lv_event_code_t event = lv_event_get_code(e);
    if(LV_EVENT_CLICKED == event)
    {
        lv_group_set_default(Screen_btn_group);
        lv_indev_set_group(indev_keypad, Screen_btn_group);

        if(obj == ui_Page_menu_btn)
        {
            printf("menu \r\n");
            ui_screen_change(ui_Screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0); 
        }
        else if(obj == ui_Page_back_btn) 
        {
            printf("back \r\n");
            ui_screen_change(ui_Screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0); 
        }
    }
}

void lv_btn_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    lv_event_code_t event = lv_event_get_code(e);

    static uint8_t child_num = 0;
    child_num = lv_obj_get_index(obj);
    
    if(LV_EVENT_FOCUSED == event)
    {
        printf("FOCUSED %d\r\n",lv_obj_get_index(obj) );
        switch(child_num)
        {
        case 0: lv_label_set_text(Screen_lab, "#f09c5a Time #");break;
        case 1: lv_label_set_text(Screen_lab, "#f09c5a Daily#");break;
        case 2: lv_label_set_text(Screen_lab, "#f09c5a Wifi #");break;
        case 3: lv_label_set_text(Screen_lab, "#f09c5a  Ble #");break;
        case 4: lv_label_set_text(Screen_lab, "#f09c5a Voice#");break;
        case 5: lv_label_set_text(Screen_lab, "#f09c5a Clock#");break;
        case 6: lv_label_set_text(Screen_lab, "#f09c5a  Set #");break;
        case 7: lv_label_set_text(Screen_lab, "#f09c5a About#");break;
        default: break;
        }      
    }
    else if(LV_EVENT_CLICKED == event)
    {
        printf("back_menu_btn_group: %d \r\n",lv_group_get_obj_count(back_menu_btn_group) );
        printf("Screen_btn_group:    %d \r\n",lv_group_get_obj_count(Screen_btn_group) );

        printf("CLICKED %d\r\n",lv_obj_get_index(obj) );
        lv_group_set_default(back_menu_btn_group);
        lv_indev_set_group(indev_keypad, back_menu_btn_group);
    
        #define lord_time 300
        switch(child_num)
        {
            case 0: ui_Screen_Time_init();  ui_screen_change(ui_Screen_Time, LV_SCR_LOAD_ANIM_MOVE_RIGHT, lord_time, 0); break;
            case 1: ui_Screen_Daily_init(); ui_screen_change(ui_Screen_Daily, LV_SCR_LOAD_ANIM_MOVE_RIGHT, lord_time, 0); break;
            case 2: ui_Screen_Wifi_init();  ui_screen_change(ui_Screen_Wifi, LV_SCR_LOAD_ANIM_MOVE_RIGHT, lord_time, 0); break;
            case 3: ui_Screen_Ble_init();   ui_screen_change(ui_Screen_Ble, LV_SCR_LOAD_ANIM_MOVE_RIGHT, lord_time, 0); break;
            case 4: ui_Screen_Voice_init(); ui_screen_change(ui_Screen_Voice, LV_SCR_LOAD_ANIM_MOVE_RIGHT, lord_time, 0); break;
            case 5: ui_Screen_Clock_init(); ui_screen_change(ui_Screen_Clock, LV_SCR_LOAD_ANIM_MOVE_RIGHT, lord_time, 0); break;
            case 6: ui_Screen_Set_init();   ui_screen_change(ui_Screen_Set, LV_SCR_LOAD_ANIM_MOVE_RIGHT, lord_time, 0); break;
            case 7: ui_Screen_About_init(); ui_screen_change(ui_Screen_About, LV_SCR_LOAD_ANIM_MOVE_RIGHT, lord_time, 0); break;
            default: break;
        }         
    }
}

void back_btn_create(lv_obj_t *obj)
{
    lv_group_remove_all_objs(back_menu_btn_group);

    ui_Page_back_btn = lv_btn_create(obj);
    lv_obj_remove_style_all(ui_Page_back_btn); 
    lv_obj_align(ui_Page_back_btn, LV_ALIGN_TOP_LEFT, 10, 10);                                                    
    lv_obj_set_size(ui_Page_back_btn, 40, 40);                                           
    lv_obj_set_style_radius(ui_Page_back_btn, 10, 0);                                               
    lv_obj_set_style_bg_color(ui_Page_back_btn, lv_color_hex(COLOR_DODGER_BLUE), 0);                
    lv_obj_set_style_bg_opa(ui_Page_back_btn, LV_OPA_0, 0);                                         
    lv_obj_set_style_bg_color(ui_Page_back_btn, lv_color_hex(COLOR_DODGER_BLUE), LV_STATE_FOCUSED); 
    lv_obj_set_style_bg_opa(ui_Page_back_btn, LV_OPA_40, LV_STATE_FOCUSED);                         
    lv_obj_set_style_bg_opa(ui_Page_back_btn, LV_OPA_60, LV_STATE_PRESSED);                         
    lv_obj_add_event_cb(ui_Page_back_btn, lv_btn_back_menu_event_cb, LV_EVENT_ALL, NULL);

    ui_Page_back_img = lv_img_create(ui_Page_back_btn);
    lv_obj_set_size(ui_Page_back_img, 40, 40);
    lv_obj_align(ui_Page_back_img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_src(ui_Page_back_img, &ui_img_back_40_png);

    ui_Page_menu_btn = lv_btn_create(obj);
    lv_obj_remove_style_all(ui_Page_menu_btn); 
    lv_obj_align(ui_Page_menu_btn, LV_ALIGN_TOP_RIGHT, -10, 10);                                                    
    lv_obj_set_size(ui_Page_menu_btn, 40, 40);                                           
    lv_obj_set_style_radius(ui_Page_menu_btn, 10, 0);                                               
    lv_obj_set_style_bg_color(ui_Page_menu_btn, lv_color_hex(COLOR_DODGER_BLUE), 0);                
    lv_obj_set_style_bg_opa(ui_Page_menu_btn, LV_OPA_0, 0);                                         
    lv_obj_set_style_bg_color(ui_Page_menu_btn, lv_color_hex(COLOR_DODGER_BLUE), LV_STATE_FOCUSED); 
    lv_obj_set_style_bg_opa(ui_Page_menu_btn, LV_OPA_40, LV_STATE_FOCUSED);                         
    lv_obj_set_style_bg_opa(ui_Page_menu_btn, LV_OPA_60, LV_STATE_PRESSED);                         
    lv_obj_add_event_cb(ui_Page_menu_btn, lv_btn_back_menu_event_cb, LV_EVENT_ALL, NULL);

    ui_Page_menu_img = lv_img_create(ui_Page_menu_btn);
    lv_obj_set_size(ui_Page_menu_img, 40, 40);
    lv_obj_align(ui_Page_menu_img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_src(ui_Page_menu_img, &ui_img_menu_40_png);

    lv_group_add_obj(back_menu_btn_group, ui_Page_back_btn);
    lv_group_add_obj(back_menu_btn_group, ui_Page_menu_btn);
}

extern int flag;

void ui_Screen_Time_init(void)
{
    ui_Screen_Time = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen_Time, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    back_btn_create(ui_Screen_Time);

    ui_ImageWatchface = lv_img_create(ui_Screen_Time);
    lv_obj_align(ui_ImageWatchface, LV_ALIGN_CENTER, 0, 15);
    lv_img_set_src(ui_ImageWatchface, &ui_img_m_background_png);
    lv_obj_set_width( ui_ImageWatchface, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_ImageWatchface, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align( ui_ImageWatchface, LV_ALIGN_CENTER );
    lv_obj_add_flag( ui_ImageWatchface, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
    lv_obj_clear_flag( ui_ImageWatchface, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

    ui_ImageArmHour = lv_img_create(ui_Screen_Time);
    lv_img_set_src(ui_ImageArmHour, &ui_img_m_hour_png);
    lv_obj_set_width( ui_ImageArmHour, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_ImageArmHour, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_ImageArmHour, 0);
    lv_obj_set_y( ui_ImageArmHour, -15 );
    lv_obj_set_align( ui_ImageArmHour, LV_ALIGN_CENTER );
    lv_obj_add_flag( ui_ImageArmHour, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
    lv_obj_clear_flag( ui_ImageArmHour, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_img_set_pivot(ui_ImageArmHour,7,66);
    lv_img_set_angle(ui_ImageArmHour,450);

    ui_ImageArmMinute = lv_img_create(ui_Screen_Time);
    lv_img_set_src(ui_ImageArmMinute, &ui_img_m_min_png);
    lv_obj_set_width( ui_ImageArmMinute, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_ImageArmMinute, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_ImageArmMinute, 0 );
    lv_obj_set_y( ui_ImageArmMinute, -37 );
    lv_obj_set_align( ui_ImageArmMinute, LV_ALIGN_CENTER );
    lv_obj_add_flag( ui_ImageArmMinute, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
    lv_obj_clear_flag( ui_ImageArmMinute, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_img_set_pivot(ui_ImageArmMinute,6,108);
    lv_img_set_angle(ui_ImageArmMinute,1800);

    ui_ImageArmSecond = lv_img_create(ui_Screen_Time);
    lv_img_set_src(ui_ImageArmSecond, &ui_img_m_sec_png);
    lv_obj_set_width( ui_ImageArmSecond, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_ImageArmSecond, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_ImageArmSecond, 0 );
    lv_obj_set_y( ui_ImageArmSecond, -32 );
    lv_obj_set_align( ui_ImageArmSecond, LV_ALIGN_CENTER );
    lv_obj_add_flag( ui_ImageArmSecond, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
    lv_obj_clear_flag( ui_ImageArmSecond, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_img_set_pivot(ui_ImageArmSecond,4,113);
    lv_img_set_angle(ui_ImageArmSecond,3150);

    clockflag = 1;
}

//page daily
static void Daily_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        if(lv_calendar_get_pressed_date(obj, &date)) {
            LV_LOG_USER("Clicked date: %02d.%02d.%d", date.day, date.month, date.year);
        }
    }
}

void ui_Screen_Daily_init(void)
{
    ui_Screen_Daily = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen_Daily, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    back_btn_create(ui_Screen_Daily);

    lv_obj_t  * calendar = lv_calendar_create(ui_Screen_Daily);
    

    lv_obj_set_size(calendar, 240, 220);
    lv_obj_align(calendar, LV_ALIGN_CENTER, 0, 30);
    lv_obj_add_event_cb(calendar, Daily_event_handler, LV_EVENT_ALL, NULL);

    lv_calendar_set_today_date(calendar, 2023, 05, 16);
    lv_calendar_set_showed_date(calendar, 2023, 05);

    // /*Highlight a few days*/
    // static lv_calendar_date_t highlighted_days[];       /*Only its pointer will be saved so should be static*/
    // highlighted_days[0].year = 2021;
    // highlighted_days[0].month = 02;
    // highlighted_days[0].day = 6;

    // lv_calendar_set_highlighted_dates(calendar, highlighted_days, 3);

    lv_calendar_header_arrow_create(calendar);
    lv_calendar_set_showed_date(calendar, 2023, 5);
}

void ui_Screen_Wifi_init(void)
{
    ui_Screen_Wifi = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen_Wifi, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    back_btn_create(ui_Screen_Wifi);

    label = lv_label_create(ui_Screen_Wifi);
    lv_obj_set_align(label, LV_ALIGN_CENTER);
    lv_label_set_text(label, "ui_Screen_Wifi");
}
lv_obj_t *ui_paly_img;
lv_obj_t *ui_play_btn;

lv_obj_t *ui_btn_img;
lv_obj_t *ui_music_img;
lv_obj_t *ui_next_btn;
lv_obj_t *ui_rewind_btn;

lv_obj_t *ui_val_up_btn;
lv_obj_t *ui_val_down_btn;

void lv_btn_play_stop_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    lv_event_code_t event = lv_event_get_code(e);
    if(LV_EVENT_CLICKED == event)
    {
        if(sec_conn)
        {
            if(obj == ui_play_btn)
            {
                if(musicflag)
                {
                    printf("stop \r\n");
                    musicflag = 0;
                    esp_hidd_send_duomeiti_value(hid_conn_id, MY_CONTROL_STOP);
                    lv_img_set_src(ui_paly_img, &ui_img_play_70_png);
                }
                else
                {
                    printf("play \r\n");
                    musicflag = 1;
                    esp_hidd_send_duomeiti_value(hid_conn_id, MY_CONTROL_START);
                    lv_img_set_src(ui_paly_img, &ui_img_stop_70_png);
                }
            }
            else if(obj == ui_next_btn)
            {
                printf("next \r\n");
                esp_hidd_send_duomeiti_value(hid_conn_id, MY_CONTROL_MUSIC_NEXT);
            }
            else if(obj == ui_rewind_btn)
            {
                printf("rewind \r\n");
                esp_hidd_send_duomeiti_value(hid_conn_id, MY_CONTROL_MUSIC_PRV);
            }
            else if(obj == ui_val_up_btn)
            {
                printf("val up \r\n");
                esp_hidd_send_duomeiti_value(hid_conn_id, MY_CONTROL_VAL_UP);
            }
            else if(obj == ui_val_down_btn)
            {
                printf("val down \r\n");
                esp_hidd_send_duomeiti_value(hid_conn_id, MY_CONTROL_VAL_DOWN);
            }
        }
        else
        {
            printf("check ble link");
        }
    }
}

void ui_Screen_Ble_init(void)
{
    ui_Screen_Ble = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen_Ble, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    back_btn_create(ui_Screen_Ble);

    ui_music_img = lv_img_create(ui_Screen_Ble);
    lv_obj_set_size(ui_music_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align(ui_music_img, LV_ALIGN_CENTER, 0, -30);
    lv_obj_add_flag( ui_music_img, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
    lv_obj_clear_flag( ui_music_img, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_img_set_pivot(ui_music_img,60,60);
    lv_img_set_src(ui_music_img, &ui_img_m_music_png);
    
    ui_rewind_btn = lv_btn_create(ui_Screen_Ble);
    lv_obj_remove_style_all(ui_rewind_btn); 
    lv_obj_set_width(ui_rewind_btn, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_rewind_btn, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_rewind_btn, -70);
    lv_obj_set_y(ui_rewind_btn, 88);
    lv_obj_set_align(ui_rewind_btn, LV_ALIGN_CENTER);                                
    lv_obj_set_style_radius(ui_rewind_btn, 20, 0);                                               
    lv_obj_set_style_bg_color(ui_rewind_btn, lv_color_hex(COLOR_DODGER_BLUE), 0);                
    lv_obj_set_style_bg_opa(ui_rewind_btn, LV_OPA_0, 0);                                         
    lv_obj_set_style_bg_color(ui_rewind_btn, lv_color_hex(COLOR_DODGER_BLUE), LV_STATE_FOCUSED); 
    lv_obj_set_style_bg_opa(ui_rewind_btn, LV_OPA_40, LV_STATE_FOCUSED);                         
    lv_obj_set_style_bg_opa(ui_rewind_btn, LV_OPA_60, LV_STATE_PRESSED);                         
    lv_obj_add_event_cb(ui_rewind_btn, lv_btn_play_stop_event_cb, LV_EVENT_ALL, NULL);

    ui_btn_img = lv_img_create(ui_rewind_btn);
    lv_obj_set_size(ui_btn_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align(ui_btn_img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_src(ui_btn_img, &ui_img_back_70_png);

    ui_play_btn = lv_btn_create(ui_Screen_Ble);
    lv_obj_remove_style_all(ui_play_btn); 
    lv_obj_set_width(ui_play_btn, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_play_btn, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_play_btn, 0);
    lv_obj_set_y(ui_play_btn, 88);
    lv_obj_set_align(ui_play_btn, LV_ALIGN_CENTER);                                
    lv_obj_set_style_radius(ui_play_btn, 20, 0);                                               
    lv_obj_set_style_bg_color(ui_play_btn, lv_color_hex(COLOR_DODGER_BLUE), 0);                
    lv_obj_set_style_bg_opa(ui_play_btn, LV_OPA_0, 0);                                         
    lv_obj_set_style_bg_color(ui_play_btn, lv_color_hex(COLOR_DODGER_BLUE), LV_STATE_FOCUSED); 
    lv_obj_set_style_bg_opa(ui_play_btn, LV_OPA_40, LV_STATE_FOCUSED);                         
    lv_obj_set_style_bg_opa(ui_play_btn, LV_OPA_60, LV_STATE_PRESSED);                         
    lv_obj_add_event_cb(ui_play_btn, lv_btn_play_stop_event_cb, LV_EVENT_ALL, NULL);

    ui_paly_img = lv_img_create(ui_play_btn);
    lv_obj_set_size(ui_paly_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align(ui_paly_img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_src(ui_paly_img, &ui_img_play_70_png);

    ui_next_btn = lv_btn_create(ui_Screen_Ble);
    lv_obj_remove_style_all(ui_next_btn); 
    lv_obj_set_width(ui_next_btn, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_next_btn, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_next_btn, 70);
    lv_obj_set_y(ui_next_btn, 88);
    lv_obj_set_align(ui_next_btn, LV_ALIGN_CENTER);                                
    lv_obj_set_style_radius(ui_next_btn, 20, 0);                                               
    lv_obj_set_style_bg_color(ui_next_btn, lv_color_hex(COLOR_DODGER_BLUE), 0);                
    lv_obj_set_style_bg_opa(ui_next_btn, LV_OPA_0, 0);                                         
    lv_obj_set_style_bg_color(ui_next_btn, lv_color_hex(COLOR_DODGER_BLUE), LV_STATE_FOCUSED); 
    lv_obj_set_style_bg_opa(ui_next_btn, LV_OPA_40, LV_STATE_FOCUSED);                         
    lv_obj_set_style_bg_opa(ui_next_btn, LV_OPA_60, LV_STATE_PRESSED);                         
    lv_obj_add_event_cb(ui_next_btn, lv_btn_play_stop_event_cb, LV_EVENT_ALL, NULL);

    ui_btn_img = lv_img_create(ui_next_btn);
    lv_obj_set_size(ui_btn_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align(ui_btn_img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_src(ui_btn_img, &ui_img_next_70_png);

    ui_val_up_btn = lv_btn_create(ui_Screen_Ble);
    lv_obj_remove_style_all(ui_val_up_btn); 
    lv_obj_set_width(ui_val_up_btn, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_val_up_btn, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_val_up_btn, 10);
    lv_obj_set_y(ui_val_up_btn, 10);
    lv_obj_set_align(ui_val_up_btn, LV_ALIGN_LEFT_MID);                                
    lv_obj_set_style_radius(ui_val_up_btn, 10, 0);                                               
    lv_obj_set_style_bg_color(ui_val_up_btn, lv_color_hex(COLOR_DODGER_BLUE), 0);                
    lv_obj_set_style_bg_opa(ui_val_up_btn, LV_OPA_0, 0);                                         
    lv_obj_set_style_bg_color(ui_val_up_btn, lv_color_hex(COLOR_DODGER_BLUE), LV_STATE_FOCUSED); 
    lv_obj_set_style_bg_opa(ui_val_up_btn, LV_OPA_40, LV_STATE_FOCUSED);                         
    lv_obj_set_style_bg_opa(ui_val_up_btn, LV_OPA_60, LV_STATE_PRESSED);                         
    lv_obj_add_event_cb(ui_val_up_btn, lv_btn_play_stop_event_cb, LV_EVENT_ALL, NULL);

    ui_btn_img = lv_img_create(ui_val_up_btn);
    lv_obj_set_size(ui_btn_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align(ui_btn_img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_src(ui_btn_img, &ui_img_hightaudio50_png);

    ui_val_down_btn = lv_btn_create(ui_Screen_Ble);
    lv_obj_remove_style_all(ui_val_down_btn); 
    lv_obj_set_width(ui_val_down_btn, LV_SIZE_CONTENT);     /// 1
    lv_obj_set_height(ui_val_down_btn, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_val_down_btn, -10);
    lv_obj_set_y(ui_val_down_btn, 10);
    lv_obj_set_align(ui_val_down_btn, LV_ALIGN_RIGHT_MID);                                
    lv_obj_set_style_radius(ui_val_down_btn, 10, 0);                                               
    lv_obj_set_style_bg_color(ui_val_down_btn, lv_color_hex(COLOR_DODGER_BLUE), 0);                
    lv_obj_set_style_bg_opa(ui_val_down_btn, LV_OPA_0, 0);                                         
    lv_obj_set_style_bg_color(ui_val_down_btn, lv_color_hex(COLOR_DODGER_BLUE), LV_STATE_FOCUSED); 
    lv_obj_set_style_bg_opa(ui_val_down_btn, LV_OPA_40, LV_STATE_FOCUSED);                         
    lv_obj_set_style_bg_opa(ui_val_down_btn, LV_OPA_60, LV_STATE_PRESSED);                         
    lv_obj_add_event_cb(ui_val_down_btn, lv_btn_play_stop_event_cb, LV_EVENT_ALL, NULL);

    ui_btn_img = lv_img_create(ui_val_down_btn);
    lv_obj_set_size(ui_btn_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align(ui_btn_img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_src(ui_btn_img, &ui_img_lowvolume50_png);
}

void ui_Screen_Voice_init(void)
{
    ui_Screen_Voice = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen_Voice, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    back_btn_create(ui_Screen_Voice);

    label = lv_label_create(ui_Screen_Voice);
    lv_obj_set_align(label, LV_ALIGN_CENTER);
    lv_label_set_text(label, "ui_Screen_Voice");
}

void ui_Screen_Clock_init(void)
{
    ui_Screen_Clock = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen_Clock, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    back_btn_create(ui_Screen_Clock);

    label = lv_label_create(ui_Screen_Clock);
    lv_obj_set_align(label, LV_ALIGN_CENTER);
    lv_label_set_text(label, "ui_Screen_Clock");
}

void ui_Screen_Set_init(void)
{
    ui_Screen_Set = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen_Set, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    back_btn_create(ui_Screen_Set);

    label = lv_label_create(ui_Screen_Set);
    lv_obj_set_align(label, LV_ALIGN_CENTER);
    lv_label_set_text(label, "ui_Screen_Set");
}

void ui_Screen_About_init(void)
{
    ui_Screen_About = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen_About, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    back_btn_create(ui_Screen_About);

    label = lv_label_create(ui_Screen_About);
    lv_obj_set_align(label, LV_ALIGN_CENTER);
    lv_label_set_text(label, "ui_Screen_About");
}



void ui_setup(void)
{
    ui_Screen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_size(ui_Screen, 240, 280);

    scrool = lv_img_create(ui_Screen);
    lv_obj_set_size(scrool, 240, 280);
    lv_obj_center(scrool);
    lv_obj_set_flex_flow(scrool, LV_FLEX_FLOW_COLUMN);
    lv_obj_add_event_cb(scrool, scroll_event_cb, LV_EVENT_SCROLL, NULL);
    //lv_obj_set_style_radius(scrool, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(scrool, true, 0);
    lv_obj_set_scroll_dir(scrool, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(scrool, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(scrool, LV_SCROLLBAR_MODE_OFF);

    Screen_lab = lv_label_create(ui_Screen);
    lv_obj_set_style_text_font(Screen_lab,&lv_font_montserrat_24,0);
    lv_obj_set_style_line_width(Screen_lab, 3, 0);
    lv_label_set_recolor(Screen_lab, true); 
    lv_obj_align(Screen_lab, LV_ALIGN_LEFT_MID, 10, 0);
    lv_label_set_text(Screen_lab, "#f09c5a Time #");

    uint8_t i;
    for(i = 0; i < 8; i++) 
    {
        Screen_btn = lv_btn_create(scrool);
        lv_obj_remove_style_all(Screen_btn);                                                     
        lv_obj_set_size(Screen_btn, 100, 100);                                           
        lv_obj_set_style_radius(Screen_btn, 20, 0);                                               
        lv_obj_set_style_bg_color(Screen_btn, lv_color_hex(COLOR_DODGER_BLUE), 0);                
        lv_obj_set_style_bg_opa(Screen_btn, LV_OPA_0, 0);                                         
        lv_obj_set_style_bg_color(Screen_btn, lv_color_hex(COLOR_DODGER_BLUE), LV_STATE_FOCUSED); 
        lv_obj_set_style_bg_opa(Screen_btn, LV_OPA_40, LV_STATE_FOCUSED);                         
        lv_obj_set_style_bg_opa(Screen_btn, LV_OPA_60, LV_STATE_PRESSED);                         
        lv_obj_add_event_cb(Screen_btn, lv_btn_event_cb, LV_EVENT_ALL, NULL);

        lv_group_add_obj(Screen_btn_group, Screen_btn);

        Screen_img = lv_img_create(Screen_btn);
        lv_obj_set_size(Screen_img, 100, 100);
        lv_obj_align(Screen_img, LV_ALIGN_CENTER, 0, 0);

        switch(i)
        {
        case 0: lv_img_set_src(Screen_img, &ui_img_time_png);  break;
        case 1: lv_img_set_src(Screen_img, &ui_img_daily_png);  break;
        case 2: lv_img_set_src(Screen_img, &ui_img_wifi_png);  break;
        case 3: lv_img_set_src(Screen_img, &ui_img_buletooth_png);  break;
        case 4: lv_img_set_src(Screen_img, &ui_img_speech_png);  break;
        case 5: lv_img_set_src(Screen_img, &ui_img_clock_png);  break;
        case 6: lv_img_set_src(Screen_img, &ui_img_tool_png);  break;
        case 7: lv_img_set_src(Screen_img, &ui_img_board_png);  break;
        }
    }

    /*Update the buttons position manually for first*/
    lv_event_send(scrool, LV_EVENT_SCROLL, NULL);
    /*Be sure the fist button is in the middle*/
    lv_obj_scroll_to_view(lv_obj_get_child(scrool, 0), LV_ANIM_OFF);

    lv_scr_load(ui_Screen);
}

void app_ui_init(void)
{
    lv_init();
    lvgl_driver_init();
    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, DISP_BUF_SIZE);

    static lv_disp_drv_t disp_drv;         /*A variable to hold the drivers. Must be static or global.*/
    lv_disp_drv_init(&disp_drv);           /*Basic initialization*/
    disp_drv.draw_buf = &draw_buf;         /*Set an initialized buffer*/
    disp_drv.flush_cb = disp_driver_flush; /*Set a flush callback to draw to the display*/
    disp_drv.hor_res = LV_HOR_RES_MAX;     /*Set the horizontal resolution in pixels*/
    disp_drv.ver_res = LV_VER_RES_MAX;     /*Set the vertical resolution in pixels*/
    disp_drv.offset_y = 20;
    lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/

    lv_port_indev_init();
    
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));
}
