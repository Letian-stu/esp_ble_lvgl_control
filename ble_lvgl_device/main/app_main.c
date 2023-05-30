/*
 * @Author: Letian-stu
 * @Date: 2023-05-05 09:18
 * @LastEditors: Letian-stu
 * @LastEditTime: 2023-05-30 13:35
 * @FilePath: /ble_lvgl_device/main/app_main.c
 * @Description: 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include <stdio.h>
#include "app_main.h"

#define TAG "main"

SemaphoreHandle_t LvglMutex;
SemaphoreHandle_t KeyreadMutex;
TaskHandle_t KeyScan_Handle;

void keyscan_Task(void *p)
{
   Button_Init();
   while (1)
   {
      if (pdTRUE == xSemaphoreTake(KeyreadMutex, portMAX_DELAY))
      {
         Button_Process();
         xSemaphoreGive(KeyreadMutex);
      }
      vTaskDelay(10 / portTICK_PERIOD_MS);
   }
}

#define ONE_MINUTE_MS   (60 * 1000)
#define ONE_HOUR_MS     (60 * 60 * 1000)
#define TWELVE_HOUR_MS  (12 * 60 * 60 * 1000)

uint16_t clockflag = 0;
uint16_t musicflag = 0;

void app_main(void)
{
   KeyreadMutex = xSemaphoreCreateMutex();
   LvglMutex = xSemaphoreCreateMutex();
   xTaskCreate(keyscan_Task, "keyscan_Task", 4096, NULL, 2, &KeyScan_Handle);

   ble_init();

   app_ui_init();

   ui_setup();
   lv_timer_handler();
   unsigned long time_msss = 0;  
   static unsigned long ms_offset = (6 * ONE_HOUR_MS) + (15 * ONE_MINUTE_MS) + 30 * 1000;
   unsigned long clock_ms;
   uint8_t hour;
   uint8_t minute;
   
   backlight_change(bckl_handle, 1);

   while (1)
   {
      vTaskDelay(pdMS_TO_TICKS(10));

      if (pdTRUE == xSemaphoreTake(LvglMutex, portMAX_DELAY))
      {
      lv_timer_handler();
         xSemaphoreGive(LvglMutex);
      }

      if(clockflag == 1)
      {
         time_msss += 10;
         clock_ms = (ms_offset + time_msss) % TWELVE_HOUR_MS;
         hour = clock_ms / ONE_HOUR_MS;
         minute = (clock_ms % ONE_HOUR_MS) / ONE_MINUTE_MS;

         //printf("ms:%ld time:%d %d %ld\r\n", clock_ms, hour, minute, clock_ms);

         int16_t angle = (clock_ms % ONE_MINUTE_MS) * 3600 / ONE_MINUTE_MS;
         lv_img_set_angle(ui_ImageArmSecond, angle);

         angle = (angle + (minute * 3600)) / 60;
         lv_img_set_angle(ui_ImageArmMinute, angle);

         angle = (angle + (hour * 3600)) / 12;
         lv_img_set_angle(ui_ImageArmHour, angle);
      }

      if(sec_conn)
      {
         if(musicflag == 0)
         {
            time_msss += 10;
            if(ui_music_img != NULL)
               lv_img_set_angle(ui_music_img, time_msss % 360000);
         }
      }

   }
}

