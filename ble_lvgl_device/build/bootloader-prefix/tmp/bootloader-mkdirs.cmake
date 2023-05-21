# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/B_Code/espidf/esp32idf_cmd/Espressif/frameworks/esp-idf-v4.4.3/components/bootloader/subproject"
  "D:/C_Github/esp_ble_lvgl_control/ble_lvgl_device/build/bootloader"
  "D:/C_Github/esp_ble_lvgl_control/ble_lvgl_device/build/bootloader-prefix"
  "D:/C_Github/esp_ble_lvgl_control/ble_lvgl_device/build/bootloader-prefix/tmp"
  "D:/C_Github/esp_ble_lvgl_control/ble_lvgl_device/build/bootloader-prefix/src/bootloader-stamp"
  "D:/C_Github/esp_ble_lvgl_control/ble_lvgl_device/build/bootloader-prefix/src"
  "D:/C_Github/esp_ble_lvgl_control/ble_lvgl_device/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/C_Github/esp_ble_lvgl_control/ble_lvgl_device/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
