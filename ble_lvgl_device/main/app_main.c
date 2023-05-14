/*
 * @Author: Letian-stu
 * @Date: 2023-05-05 09:18
 * @LastEditors: Letian-stu
 * @LastEditTime: 2023-05-14 13:54
 * @FilePath: /ble_lvgl_device/main/app_main.c
 * @Description: 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "app_ui.h"
#include "button.h"

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

void app_main(void)
{
   KeyreadMutex = xSemaphoreCreateMutex();
   xTaskCreate(keyscan_Task, "keyscan_Task", 4096, NULL, 5, &KeyScan_Handle);

   app_ui_init();

   ui_setup();
   while (1)
   {
      vTaskDelay(pdMS_TO_TICKS(10));
      lv_timer_handler();
   }
}

