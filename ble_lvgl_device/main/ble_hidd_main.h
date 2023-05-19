/*
 * @Author: Letian-stu
 * @Date: 2023-05-18 10:50
 * @LastEditors: Letian-stu
 * @LastEditTime: 2023-05-19 09:52
 * @FilePath: /ble_lvgl_device/main/ble_hidd_main.h
 * @Description: 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"

#include "esp_hidd_prf_api.h"
#include "esp_bt_defs.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_gatt_defs.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "driver/gpio.h"
#include "hid_dev.h"

extern bool sec_conn;

// extern bool send_volum_up;
extern bool sec_conn;
extern uint16_t hid_conn_id;

void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
void hidd_event_callback(esp_hidd_cb_event_t event, esp_hidd_cb_param_t *param);
void hid_demo_task(void *pvParameters);
void ble_init(void);