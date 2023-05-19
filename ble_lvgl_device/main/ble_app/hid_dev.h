// Copyright 2017-2018 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef HID_DEV_H__
#define HID_DEV_H__

#include "hidd_le_prf_int.h"


#ifdef __cplusplus
extern "C" {
#endif


/* HID Report type */
#define HID_TYPE_INPUT       1
#define HID_TYPE_OUTPUT      2
#define HID_TYPE_FEATURE     3

// HID Keyboard/Keypad Usage IDs (subset of the codes available in the USB HID Usage Tables spec)
/*
#define HID_KEY_RESERVED       0    // No event inidicated
#define HID_KEY_A              4    // Keyboard a and A
#define HID_KEY_B              5    // Keyboard b and B
#define HID_KEY_C              6    // Keyboard c and C
#define HID_KEY_D              7    // Keyboard d and D
#define HID_KEY_E              8    // Keyboard e and E
#define HID_KEY_F              9    // Keyboard f and F
#define HID_KEY_G              10   // Keyboard g and G
#define HID_KEY_H              11   // Keyboard h and H
#define HID_KEY_I              12   // Keyboard i and I
#define HID_KEY_J              13   // Keyboard j and J
#define HID_KEY_K              14   // Keyboard k and K
#define HID_KEY_L              15   // Keyboard l and L
#define HID_KEY_M              16   // Keyboard m and M
#define HID_KEY_N              17   // Keyboard n and N
#define HID_KEY_O              18   // Keyboard o and O
#define HID_KEY_P              19   // Keyboard p and p
#define HID_KEY_Q              20   // Keyboard q and Q
#define HID_KEY_R              21   // Keyboard r and R
#define HID_KEY_S              22   // Keyboard s and S
#define HID_KEY_T              23   // Keyboard t and T
#define HID_KEY_U              24   // Keyboard u and U
#define HID_KEY_V              25   // Keyboard v and V
#define HID_KEY_W              26   // Keyboard w and W
#define HID_KEY_X              27   // Keyboard x and X
#define HID_KEY_Y              28   // Keyboard y and Y
#define HID_KEY_Z              29   // Keyboard z and Z
#define HID_KEY_1              30   // Keyboard 1 and !
#define HID_KEY_2              31   // Keyboard 2 and @
#define HID_KEY_3              32   // Keyboard 3 and #
#define HID_KEY_4              33   // Keyboard 4 and %
#define HID_KEY_5              34   // Keyboard 5 and %
#define HID_KEY_6              35   // Keyboard 6 and ^
#define HID_KEY_7              36   // Keyboard 7 and &
#define HID_KEY_8              37   // Keyboard 8 and *
#define HID_KEY_9              38   // Keyboard 9 and (
#define HID_KEY_0              39   // Keyboard 0 and )
#define HID_KEY_RETURN         40   // Keyboard Return (ENTER)
#define HID_KEY_ESCAPE         41   // Keyboard ESCAPE
#define HID_KEY_DELETE         42   // Keyboard DELETE (Backspace)
#define HID_KEY_TAB            43   // Keyboard Tab
#define HID_KEY_SPACEBAR       44   // Keyboard Spacebar
#define HID_KEY_MINUS          45   // Keyboard - and (underscore)
#define HID_KEY_EQUAL          46   // Keyboard = and +
#define HID_KEY_LEFT_BRKT      47   // Keyboard [ and {
#define HID_KEY_RIGHT_BRKT     48   // Keyboard ] and }
#define HID_KEY_BACK_SLASH     49   // Keyboard \ and |
#define HID_KEY_SEMI_COLON     51   // Keyboard ; and :
#define HID_KEY_SGL_QUOTE      52   // Keyboard ' and "
#define HID_KEY_GRV_ACCENT     53   // Keyboard Grave Accent and Tilde
#define HID_KEY_COMMA          54   // Keyboard , and <
#define HID_KEY_DOT            55   // Keyboard . and >
#define HID_KEY_FWD_SLASH      56   // Keyboard / and ?
#define HID_KEY_CAPS_LOCK      57   // Keyboard Caps Lock
#define HID_KEY_F1             58   // Keyboard F1
#define HID_KEY_F2             59   // Keyboard F2
#define HID_KEY_F3             60   // Keyboard F3
#define HID_KEY_F4             61   // Keyboard F4
#define HID_KEY_F5             62   // Keyboard F5
#define HID_KEY_F6             63   // Keyboard F6
#define HID_KEY_F7             64   // Keyboard F7
#define HID_KEY_F8             65   // Keyboard F8
#define HID_KEY_F9             66   // Keyboard F9
#define HID_KEY_F10            67   // Keyboard F10
#define HID_KEY_F11            68   // Keyboard F11
#define HID_KEY_F12            69   // Keyboard F12
#define HID_KEY_PRNT_SCREEN    70   // Keyboard Print Screen
#define HID_KEY_SCROLL_LOCK    71   // Keyboard Scroll Lock
#define HID_KEY_PAUSE          72   // Keyboard Pause
#define HID_KEY_INSERT         73   // Keyboard Insert
#define HID_KEY_HOME           74   // Keyboard Home
#define HID_KEY_PAGE_UP        75   // Keyboard PageUp
#define HID_KEY_DELETE_FWD     76   // Keyboard Delete Forward
#define HID_KEY_END            77   // Keyboard End
#define HID_KEY_PAGE_DOWN      78   // Keyboard PageDown
#define HID_KEY_RIGHT_ARROW    79   // Keyboard RightArrow
#define HID_KEY_LEFT_ARROW     80   // Keyboard LeftArrow
#define HID_KEY_DOWN_ARROW     81   // Keyboard DownArrow
#define HID_KEY_UP_ARROW       82   // Keyboard UpArrow
#define HID_KEY_NUM_LOCK       83   // Keypad Num Lock and Clear
#define HID_KEY_DIVIDE         84   // Keypad /
#define HID_KEY_MULTIPLY       85   // Keypad *
#define HID_KEY_SUBTRACT       86   // Keypad -
#define HID_KEY_ADD            87   // Keypad +
#define HID_KEY_ENTER          88   // Keypad ENTER
#define HID_KEYPAD_1           89   // Keypad 1 and End
#define HID_KEYPAD_2           90   // Keypad 2 and Down Arrow
#define HID_KEYPAD_3           91   // Keypad 3 and PageDn
#define HID_KEYPAD_4           92   // Keypad 4 and Lfet Arrow
#define HID_KEYPAD_5           93   // Keypad 5
#define HID_KEYPAD_6           94   // Keypad 6 and Right Arrow
#define HID_KEYPAD_7           95   // Keypad 7 and Home
#define HID_KEYPAD_8           96   // Keypad 8 and Up Arrow
#define HID_KEYPAD_9           97   // Keypad 9 and PageUp
#define HID_KEYPAD_0           98   // Keypad 0 and Insert
#define HID_KEYPAD_DOT         99   // Keypad . and Delete
#define HID_KEY_MUTE           127  // Keyboard Mute
#define HID_KEY_VOLUME_UP      128  // Keyboard Volume up
#define HID_KEY_VOLUME_DOWN    129  // Keyboard Volume down
#define HID_KEY_LEFT_CTRL      224  // Keyboard LeftContorl
#define HID_KEY_LEFT_SHIFT     225  // Keyboard LeftShift
#define HID_KEY_LEFT_ALT       226  // Keyboard LeftAlt
#define HID_KEY_LEFT_GUI       227  // Keyboard LeftGUI
#define HID_KEY_RIGHT_CTRL     228  // Keyboard LeftContorl
#define HID_KEY_RIGHT_SHIFT    229  // Keyboard LeftShift
#define HID_KEY_RIGHT_ALT      230  // Keyboard LeftAlt
#define HID_KEY_RIGHT_GUI      231  // Keyboard RightGUI
typedef uint8_t keyboard_cmd_t;

#define HID_MOUSE_LEFT       253
#define HID_MOUSE_MIDDLE     254
#define HID_MOUSE_RIGHT      255
typedef uint8_t mouse_cmd_t;
*/

//--------------------------------------------------------------------+
// HID KEYCODE
//--------------------------------------------------------------------+
/*******************************添加*************************************/
#define HID_KEY_NONE                      0x00
#define HID_KEY_A                         0x04
#define HID_KEY_B                         0x05
#define HID_KEY_C                         0x06
#define HID_KEY_D                         0x07
#define HID_KEY_E                         0x08
#define HID_KEY_F                         0x09
#define HID_KEY_G                         0x0A
#define HID_KEY_H                         0x0B
#define HID_KEY_I                         0x0C
#define HID_KEY_J                         0x0D
#define HID_KEY_K                         0x0E
#define HID_KEY_L                         0x0F
#define HID_KEY_M                         0x10
#define HID_KEY_N                         0x11
#define HID_KEY_O                         0x12
#define HID_KEY_P                         0x13
#define HID_KEY_Q                         0x14
#define HID_KEY_R                         0x15
#define HID_KEY_S                         0x16
#define HID_KEY_T                         0x17
#define HID_KEY_U                         0x18
#define HID_KEY_V                         0x19
#define HID_KEY_W                         0x1A
#define HID_KEY_X                         0x1B
#define HID_KEY_Y                         0x1C
#define HID_KEY_Z                         0x1D
#define HID_KEY_1                         0x1E
#define HID_KEY_2                         0x1F
#define HID_KEY_3                         0x20
#define HID_KEY_4                         0x21
#define HID_KEY_5                         0x22
#define HID_KEY_6                         0x23
#define HID_KEY_7                         0x24
#define HID_KEY_8                         0x25
#define HID_KEY_9                         0x26
#define HID_KEY_0                         0x27
#define HID_KEY_ENTER                     0x28
#define HID_KEY_ESCAPE                    0x29
#define HID_KEY_BACKSPACE                 0x2A
#define HID_KEY_TAB                       0x2B
#define HID_KEY_SPACE                     0x2C
#define HID_KEY_MINUS                     0x2D
#define HID_KEY_EQUAL                     0x2E
#define HID_KEY_BRACKET_LEFT              0x2F
#define HID_KEY_BRACKET_RIGHT             0x30
#define HID_KEY_BACKSLASH                 0x31
#define HID_KEY_EUROPE_1                  0x32
#define HID_KEY_SEMICOLON                 0x33
#define HID_KEY_APOSTROPHE                0x34
#define HID_KEY_GRAVE                     0x35
#define HID_KEY_COMMA                     0x36
#define HID_KEY_PERIOD                    0x37
#define HID_KEY_SLASH                     0x38
#define HID_KEY_CAPS_LOCK                 0x39
#define HID_KEY_F1                        0x3A
#define HID_KEY_F2                        0x3B
#define HID_KEY_F3                        0x3C
#define HID_KEY_F4                        0x3D
#define HID_KEY_F5                        0x3E
#define HID_KEY_F6                        0x3F
#define HID_KEY_F7                        0x40
#define HID_KEY_F8                        0x41
#define HID_KEY_F9                        0x42
#define HID_KEY_F10                       0x43
#define HID_KEY_F11                       0x44
#define HID_KEY_F12                       0x45
#define HID_KEY_PRINT_SCREEN              0x46
#define HID_KEY_SCROLL_LOCK               0x47
#define HID_KEY_PAUSE                     0x48
#define HID_KEY_INSERT                    0x49
#define HID_KEY_HOME                      0x4A
#define HID_KEY_PAGE_UP                   0x4B
#define HID_KEY_DELETE                    0x4C
#define HID_KEY_END                       0x4D
#define HID_KEY_PAGE_DOWN                 0x4E
#define HID_KEY_ARROW_RIGHT               0x4F
#define HID_KEY_ARROW_LEFT                0x50
#define HID_KEY_ARROW_DOWN                0x51
#define HID_KEY_ARROW_UP                  0x52
#define HID_KEY_NUM_LOCK                  0x53
#define HID_KEY_KEYPAD_DIVIDE             0x54
#define HID_KEY_KEYPAD_MULTIPLY           0x55
#define HID_KEY_KEYPAD_SUBTRACT           0x56
#define HID_KEY_KEYPAD_ADD                0x57
#define HID_KEY_KEYPAD_ENTER              0x58
#define HID_KEY_KEYPAD_1                  0x59
#define HID_KEY_KEYPAD_2                  0x5A
#define HID_KEY_KEYPAD_3                  0x5B
#define HID_KEY_KEYPAD_4                  0x5C
#define HID_KEY_KEYPAD_5                  0x5D
#define HID_KEY_KEYPAD_6                  0x5E
#define HID_KEY_KEYPAD_7                  0x5F
#define HID_KEY_KEYPAD_8                  0x60
#define HID_KEY_KEYPAD_9                  0x61
#define HID_KEY_KEYPAD_0                  0x62
#define HID_KEY_KEYPAD_DECIMAL            0x63
#define HID_KEY_EUROPE_2                  0x64
#define HID_KEY_APPLICATION               0x65
#define HID_KEY_POWER                     0x66
#define HID_KEY_KEYPAD_EQUAL              0x67
#define HID_KEY_F13                       0x68
#define HID_KEY_F14                       0x69
#define HID_KEY_F15                       0x6A
#define HID_KEY_F16                       0x6B
#define HID_KEY_F17                       0x6C
#define HID_KEY_F18                       0x6D
#define HID_KEY_F19                       0x6E
#define HID_KEY_F20                       0x6F
#define HID_KEY_F21                       0x70
#define HID_KEY_F22                       0x71
#define HID_KEY_F23                       0x72
#define HID_KEY_F24                       0x73
#define HID_KEY_EXECUTE                   0x74
#define HID_KEY_HELP                      0x75
#define HID_KEY_MENU                      0x76
#define HID_KEY_SELECT                    0x77
#define HID_KEY_STOP                      0x78
#define HID_KEY_AGAIN                     0x79
#define HID_KEY_UNDO                      0x7A
#define HID_KEY_CUT                       0x7B
#define HID_KEY_COPY                      0x7C
#define HID_KEY_PASTE                     0x7D
#define HID_KEY_FIND                      0x7E
#define HID_KEY_MUTE                      0x7F
#define HID_KEY_VOLUME_UP                 0x80
#define HID_KEY_VOLUME_DOWN               0x81
#define HID_KEY_LOCKING_CAPS_LOCK         0x82
#define HID_KEY_LOCKING_NUM_LOCK          0x83
#define HID_KEY_LOCKING_SCROLL_LOCK       0x84
#define HID_KEY_KEYPAD_COMMA              0x85
#define HID_KEY_KEYPAD_EQUAL_SIGN         0x86
#define HID_KEY_KANJI1                    0x87
#define HID_KEY_KANJI2                    0x88
#define HID_KEY_KANJI3                    0x89
#define HID_KEY_KANJI4                    0x8A
#define HID_KEY_KANJI5                    0x8B
#define HID_KEY_KANJI6                    0x8C
#define HID_KEY_KANJI7                    0x8D
#define HID_KEY_KANJI8                    0x8E
#define HID_KEY_KANJI9                    0x8F
#define HID_KEY_LANG1                     0x90
#define HID_KEY_LANG2                     0x91
#define HID_KEY_LANG3                     0x92
#define HID_KEY_LANG4                     0x93
#define HID_KEY_LANG5                     0x94
#define HID_KEY_LANG6                     0x95
#define HID_KEY_LANG7                     0x96
#define HID_KEY_LANG8                     0x97
#define HID_KEY_LANG9                     0x98
#define HID_KEY_ALTERNATE_ERASE           0x99
#define HID_KEY_SYSREQ_ATTENTION          0x9A
#define HID_KEY_CANCEL                    0x9B
#define HID_KEY_CLEAR                     0x9C
#define HID_KEY_PRIOR                     0x9D
#define HID_KEY_RETURN                    0x9E
#define HID_KEY_SEPARATOR                 0x9F
#define HID_KEY_OUT                       0xA0
#define HID_KEY_OPER                      0xA1
#define HID_KEY_CLEAR_AGAIN               0xA2
#define HID_KEY_CRSEL_PROPS               0xA3
#define HID_KEY_EXSEL                     0xA4
// RESERVED					                      0xA5-DF
#define HID_KEY_CONTROL_LEFT              0xE0
#define HID_KEY_SHIFT_LEFT                0xE1
#define HID_KEY_ALT_LEFT                  0xE2
#define HID_KEY_GUI_LEFT                  0xE3
#define HID_KEY_CONTROL_RIGHT             0xE4
#define HID_KEY_SHIFT_RIGHT               0xE5
#define HID_KEY_ALT_RIGHT                 0xE6
#define HID_KEY_GUI_RIGHT                 0xE7
typedef uint8_t keyboard_cmd_t;

#define HID_MOUSE_LEFT       253
#define HID_MOUSE_MIDDLE     254
#define HID_MOUSE_RIGHT      255
typedef uint8_t mouse_cmd_t;

/****************************************************************/



// HID Consumer Usage IDs (subset of the codes available in the USB HID Usage Tables spec)
#define HID_CONSUMER_POWER          48  // Power
#define HID_CONSUMER_RESET          49  // Reset
#define HID_CONSUMER_SLEEP          50  // Sleep

#define HID_CONSUMER_MENU           64  // Menu
#define HID_CONSUMER_SELECTION      128 // Selection
#define HID_CONSUMER_ASSIGN_SEL     129 // Assign Selection
#define HID_CONSUMER_MODE_STEP      130 // Mode Step
#define HID_CONSUMER_RECALL_LAST    131 // Recall Last
#define HID_CONSUMER_QUIT           148 // Quit
#define HID_CONSUMER_HELP           149 // Help
#define HID_CONSUMER_CHANNEL_UP     156 // Channel Increment
#define HID_CONSUMER_CHANNEL_DOWN   157 // Channel Decrement

#define HID_CONSUMER_PLAY           176 // Play
#define HID_CONSUMER_PAUSE          177 // Pause
#define HID_CONSUMER_RECORD         178 // Record
#define HID_CONSUMER_FAST_FORWARD   179 // Fast Forward
#define HID_CONSUMER_REWIND         180 // Rewind
#define HID_CONSUMER_SCAN_NEXT_TRK  181 // Scan Next Track
#define HID_CONSUMER_SCAN_PREV_TRK  182 // Scan Previous Track
#define HID_CONSUMER_STOP           183 // Stop
#define HID_CONSUMER_EJECT          184 // Eject
#define HID_CONSUMER_RANDOM_PLAY    185 // Random Play
#define HID_CONSUMER_SELECT_DISC    186 // Select Disk
#define HID_CONSUMER_ENTER_DISC     187 // Enter Disc
#define HID_CONSUMER_REPEAT         188 // Repeat
#define HID_CONSUMER_STOP_EJECT     204 // Stop/Eject
#define HID_CONSUMER_PLAY_PAUSE     205 // Play/Pause
#define HID_CONSUMER_PLAY_SKIP      206 // Play/Skip

#define HID_CONSUMER_VOLUME         224 // Volume
#define HID_CONSUMER_BALANCE        225 // Balance
#define HID_CONSUMER_MUTE           226 // Mute
#define HID_CONSUMER_BASS           227 // Bass
#define HID_CONSUMER_VOLUME_UP      233 // Volume Increment
#define HID_CONSUMER_VOLUME_DOWN    234 // Volume Decrement
typedef uint8_t consumer_cmd_t;

#define HID_CC_RPT_MUTE                 1
#define HID_CC_RPT_POWER                2
#define HID_CC_RPT_LAST                 3
#define HID_CC_RPT_ASSIGN_SEL           4
#define HID_CC_RPT_PLAY                 5
#define HID_CC_RPT_PAUSE                6
#define HID_CC_RPT_RECORD               7
#define HID_CC_RPT_FAST_FWD             8
#define HID_CC_RPT_REWIND               9
#define HID_CC_RPT_SCAN_NEXT_TRK        10
#define HID_CC_RPT_SCAN_PREV_TRK        11
#define HID_CC_RPT_STOP                 12

#define HID_CC_RPT_CHANNEL_UP           0x01
#define HID_CC_RPT_CHANNEL_DOWN         0x03
#define HID_CC_RPT_VOLUME_UP            0x40
#define HID_CC_RPT_VOLUME_DOWN          0x80

// HID Consumer Control report bitmasks
#define HID_CC_RPT_NUMERIC_BITS         0xF0
#define HID_CC_RPT_CHANNEL_BITS         0xCF
#define HID_CC_RPT_VOLUME_BITS          0x3F
#define HID_CC_RPT_BUTTON_BITS          0xF0
#define HID_CC_RPT_SELECTION_BITS       0xCF

//多媒体控制				
//0.开启       1.暂停
//2.亮度增大    3.亮度减弱
//4.下一曲      5.上一曲
//6.音量增大    7.音量减小
#ifdef DUOMEITI

#define MY_CONTROL_START            (uint16_t)(1 << 0)
#define MY_CONTROL_STOP             (uint16_t)(1 << 1)
#define MY_CONTROL_MUSIC_NEXT       (uint16_t)(1 << 2)
#define MY_CONTROL_MUSIC_PRV        (uint16_t)(1 << 3)
#define MY_CONTROL_VAL_UP           (uint16_t)(1 << 4)
#define MY_CONTROL_VAL_DOWN         (uint16_t)(1 << 5)
#define MY_CONTROL_LIGHT_UP         (uint16_t)(1 << 6)
#define MY_CONTROL_LIGHT_DOWN       (uint16_t)(1 << 7)

#endif


// Macros for the HID Consumer Control 2-byte report
#define HID_CC_RPT_SET_NUMERIC(s, x)    (s)[0] &= HID_CC_RPT_NUMERIC_BITS;   \
                                        (s)[0] = (x)
#define HID_CC_RPT_SET_CHANNEL(s, x)    (s)[0] &= HID_CC_RPT_CHANNEL_BITS;   \
                                        (s)[0] |= ((x) & 0x03) << 4
#define HID_CC_RPT_SET_VOLUME_UP(s)     (s)[0] &= HID_CC_RPT_VOLUME_BITS;    \
                                        (s)[0] |= 0x40
#define HID_CC_RPT_SET_VOLUME_DOWN(s)   (s)[0] &= HID_CC_RPT_VOLUME_BITS;    \
                                        (s)[0] |= 0x80
#define HID_CC_RPT_SET_BUTTON(s, x)     (s)[1] &= HID_CC_RPT_BUTTON_BITS;    \
                                        (s)[1] |= (x)
#define HID_CC_RPT_SET_SELECTION(s, x)  (s)[1] &= HID_CC_RPT_SELECTION_BITS; \
                                        (s)[1] |= ((x) & 0x03) << 4


// HID report mapping table
typedef struct
{
  uint16_t    handle;           // Handle of report characteristic
  uint16_t    cccdHandle;       // Handle of CCCD for report characteristic
  uint8_t     id;               // Report ID
  uint8_t     type;             // Report type
  uint8_t     mode;             // Protocol mode (report or boot)
} hid_report_map_t;

// HID dev configuration structure
typedef struct
{
  uint32_t    idleTimeout;      // Idle timeout in milliseconds
  uint8_t     hidFlags;         // HID feature flags

} hid_dev_cfg_t;

void hid_dev_register_reports(uint8_t num_reports, hid_report_map_t *p_report);

void hid_dev_send_report(esp_gatt_if_t gatts_if, uint16_t conn_id,
                                    uint8_t id, uint8_t type, uint8_t length, uint8_t *data);

void hid_consumer_build_report(uint8_t *buffer, consumer_cmd_t cmd);

void hid_keyboard_build_report(uint8_t *buffer, keyboard_cmd_t cmd);

void hid_mouse_build_report(uint8_t *buffer, mouse_cmd_t cmd);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* HID_DEV_H__ */
