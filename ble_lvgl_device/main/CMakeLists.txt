idf_component_register(SRCS 
                        # "ble_app/ble_hidd_demo_main.c"
                        "ble_app/esp_hidd_prf_api.c"
                        "ble_app/hid_dev.c"
                        "ble_app/hid_device_le_prf.c"

                        "app_main.c" 
                        "ble_hidd_main.c"

                        "lv_ui/app_ui.c" 
                        "lv_ui/lv_port_indev.c" 
                        
                        "lv_ui/img/ui_img_bg_png.c" 
                        "lv_ui/img/ui_img_buletooth_png.c" 
                        "lv_ui/img/ui_img_clock_png.c" 
                        "lv_ui/img/ui_img_daily_png.c" 
                        "lv_ui/img/ui_img_speech_png.c" 
                        "lv_ui/img/ui_img_time_png.c" 
                        "lv_ui/img/ui_img_tool_png.c" 
                        "lv_ui/img/ui_img_wifi_png.c" 
                        "lv_ui/img/ui_img_board_png.c" 
                        "lv_ui/img/ui_img_back_40_png.c" 
                        "lv_ui/img/ui_img_menu_40_png.c" 

                        "lv_ui/img/ui_img_m_hour_png.c" 
                        "lv_ui/img/ui_img_m_min_png.c" 
                        "lv_ui/img/ui_img_m_sec_png.c" 
                        "lv_ui/img/ui_img_m_background_png.c" 

                        "lv_ui/img/ui_img_stop_70_png.c" 
                        "lv_ui/img/ui_img_play_70_png.c" 
                        "lv_ui/img/ui_img_next_70_png.c" 
                        "lv_ui/img/ui_img_back_70_png.c" 
                        "lv_ui/img/ui_img_m_music_png.c" 

                        "lv_ui/img/ui_img_hightspeaker70_png.c" 
                        "lv_ui/img/ui_img_lowvolume70_png.c" 

                        "lv_ui/img/ui_img_lowvolume50_png.c" 
                        "lv_ui/img/ui_img_hightaudio50_png.c" 

                        INCLUDE_DIRS "."
                        "lv_ui" 
                        "ble_app" 
                        )

target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-unused-const-variable)


