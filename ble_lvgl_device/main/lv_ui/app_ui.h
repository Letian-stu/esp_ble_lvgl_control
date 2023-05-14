/*
 * @Author: Letian-stu
 * @Date: 2023-05-12 14:55
 * @LastEditors: Letian-stu
 * @LastEditTime: 2023-05-14 13:40
 * @FilePath: /ble_lvgl_device/main/lv_ui/app_ui.h
 * @Description: 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include "lvgl.h"
#include "lvgl_helpers.h"
#include "lv_port_indev.h"

#define LV_TICK_PERIOD_MS 1

#define COLOR_DODGER_BLUE    0x1e90ff
#define COLOR_PURPLE         0xa020f0
#define COLOR_write			 0xffffff
#define COLOR_black			 0x000000

extern lv_group_t *Screen_btn_group;
extern lv_group_t *back_menu_btn_group;

LV_IMG_DECLARE(ui_img_bg_png);
LV_IMG_DECLARE(ui_img_buletooth_png);   
LV_IMG_DECLARE(ui_img_board_png);
LV_IMG_DECLARE(ui_img_clock_png); 
LV_IMG_DECLARE(ui_img_daily_png); 
LV_IMG_DECLARE(ui_img_speech_png); 
LV_IMG_DECLARE(ui_img_time_png); 
LV_IMG_DECLARE(ui_img_tool_png);  
LV_IMG_DECLARE(ui_img_wifi_png);
LV_IMG_DECLARE(ui_img_back_40_png);
LV_IMG_DECLARE(ui_img_menu_40_png);

void ui_setup(void);
void ui_Screen_Time_init(void);
void ui_Screen_Daily_init(void);
void ui_Screen_Wifi_init(void);
void ui_Screen_Ble_init(void);
void ui_Screen_Voice_init(void);
void ui_Screen_Clock_init(void);
void ui_Screen_Set_init(void);
void ui_Screen_About_init(void);
void ui_setup(void);
void app_ui_init(void);
