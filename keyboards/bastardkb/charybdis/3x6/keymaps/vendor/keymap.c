/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#ifdef MACCEL_ENABLE
    #include "maccel/maccel.h"
#endif

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_QWERTY,
    LAYER_NAV,
    LAYER_NUMBER,
    LAYER_BROWSE,
    LAYER_MEDIA,
    LAYER_SYMBOL,
    LAYER_INTERNALS,
    LAYER_POINTER,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
//#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)
#define RSFT_GV MT(MOD_RSFT, KC_GRAVE)
#define NAV_ENT LT(LAYER_NAV, KC_ENTER)
#define NAV_SPC LT(LAYER_NAV, KC_SPC)
#define MEDIA LT(LAYER_MEDIA, KC_MPLY)
#define SYM_TAB LT(LAYER_SYMBOL, KC_TAB)
#define LC_TAB MT(MOD_LCTL, KC_TAB)
#define SFT_ESC MT(MOD_LSFT, KC_ESC)
#define SPC_NUM LT(LAYER_NUMBER, KC_SPC)
#define LGUI_CBS MT(MOD_LGUI, KC_BSPC)
#define BROWSE_CBS LT(LAYER_BROWSE, KC_BSPC)

enum custom_keycodes {
     FAKE_MOD = SAFE_RANGE,
 };
 bool fake_mod_active = false;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     [LAYER_BASE] = LAYOUT(
     // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          SYM_TAB,   KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,      KC_Z,    KC_F,    KC_O,    KC_U, KC_QUOTE,  KC_MINUS,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          LC_TAB,    KC_C,    KC_R,    KC_S,    KC_T,    KC_G,      KC_M,    KC_N,    KC_E,    KC_I,     KC_A,  KC_BSPC,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          SFT_ESC,   KC_Q,    KC_J,    KC_V,    KC_D,    KC_K,      KC_X,    KC_H,   KC_SLSH, KC_COMM,  KC_DOT, C(KC_BSPC),
     // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                           LGUI_CBS,  NAV_SPC, MO(LAYER_BROWSE),  NAV_ENT,  SPC_NUM
     //                            ╰───────────────────────────╯ ╰──────────────────╯
     ),

     [LAYER_QWERTY] = LAYOUT(
     // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          _______,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, _______,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          _______,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, _______,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          _______,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, _______,
     // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   _______,  KC_LALT,   KC_LALT,      _______,  _______
     //                            ╰───────────────────────────╯ ╰──────────────────╯
     ),

     [LAYER_NAV] = LAYOUT(
     // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          _______, _______, _______, KC_END,  _______, _______,    _______,  _______,  _______, _______, _______, MO(LAYER_INTERNALS),
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          _______, KC_HOME, _______, KC_DEL, C(KC_RGHT),C(KC_HOME), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_BSPC, _______,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          _______, _______, _______, _______,  EE_CLR, C(KC_LEFT), _______,    _______,    _______,    _______, _______, _______,
     // ╰─────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                        _______, KC_LSFT, _______,    _______, KC_LSFT
     //                            ╰───────────────────────────╯ ╰──────────────────╯
     ),

     [LAYER_NUMBER] = LAYOUT(
     // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          XXXXXXX, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),      S(KC_6), S(KC_7),  S(KC_8), KC_MINUS, KC_F10, KC_F11,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,     KC_7,    KC_8,    KC_9,    KC_0, _______,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          XXXXXXX, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                KC_F6, KC_F7, KC_F8, KC_F9, KC_DOT, KC_F12,
     // ╰─────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                        XXXXXXX, XXXXXXX, _______,    XXXXXXX, _______
     //                            ╰───────────────────────────╯ ╰──────────────────╯
     ),


     [LAYER_BROWSE] = LAYOUT(
     // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          MO(LAYER_INTERNALS), XXXXXXX, C(KC_W), XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          KC_LCTL, XXXXXXX, XXXXXXX, MEDIA, XXXXXXX, XXXXXXX,        A(KC_LEFT), C(KC_TAB), C(S(KC_TAB)), A(KC_RGHT), XXXXXXX, XXXXXXX,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          FAKE_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     // ╰─────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                        XXXXXXX, XXXXXXX, _______,    XXXXXXX, _______
     //                            ╰───────────────────────────╯ ╰──────────────────╯
     ),

     [LAYER_MEDIA] = LAYOUT(
          // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
               XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
               XXXXXXX, XXXXXXX, KC_MPRV, XXXXXXX, KC_MNXT, KC_MUTE,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
               XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          // ╰─────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                             XXXXXXX, XXXXXXX, _______,    XXXXXXX, _______
          //                            ╰───────────────────────────╯ ╰──────────────────╯
          ),

     [LAYER_SYMBOL] = LAYOUT(
          // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
               _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, LSFT(KC_LBRC), KC_EQUAL, LSFT(KC_RBRC), KC_MINUS, KC_SCLN,
          // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
               _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_LBRC, LSFT(KC_9), KC_BSLS, LSFT(KC_0), KC_LBRC, C(KC_SCLN),
          // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
               _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, KC_MINUS, S(KC_MINUS), KC_GRAVE,
          // ╰─────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                             XXXXXXX, KC_LSFT, _______,    KC_LSFT, _______
          //                            ╰───────────────────────────╯ ╰──────────────────╯
          ),

     //   [LAYER_LOWER] = LAYOUT(
     //      // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
     //           XXXXXXX, RGB_TOG, KC_MNXT, KC_MPLY, KC_MPRV, XXXXXXX,    KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC, XXXXXXX,
     //      // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
     //           XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    KC_PPLS,    KC_4,    KC_5,    KC_6, KC_PMNS, XXXXXXX,
     //      // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
     //           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  EE_CLR, QK_BOOT,    KC_PAST,    KC_1,    KC_2,    KC_3, KC_PSLS, XXXXXXX,
     //      // ╰─────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
     //                                      XXXXXXX, XXXXXXX, _______,    XXXXXXX, _______
     //      //                            ╰───────────────────────────╯ ╰──────────────────╯
     //      ),

     //      [LAYER_RAISE] = LAYOUT(
     //           // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
     //                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_VOLU, KC_MUTE, KC_VOLD, XXXXXXX, XXXXXXX,
     //           // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
     //                XXXXXXX, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
     //           // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
     //                XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, XXXXXXX,    QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     //           // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
     //                                           _______, _______, XXXXXXX,    _______, XXXXXXX
     //           //                            ╰───────────────────────────╯ ╰──────────────────╯
     //           ),

     [LAYER_INTERNALS] = LAYOUT(
          // ╭──────────────────────────────────────────────────────╮  ╭──────────────────────────────────────────────────────╮
               S_D_MOD,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          // ├──────────────────────────────────────────────────────┤  ├──────────────────────────────────────────────────────┤
               S_D_RMOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DPI_RMOD,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          // ├──────────────────────────────────────────────────────┤  ├──────────────────────────────────────────────────────┤
               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR, QK_BOOT,        QK_BOOT, EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          // ╰─────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                             XXXXXXX, XXXXXXX, _______,    XXXXXXX, _______
          //                            ╰───────────────────────────╯ ╰──────────────────╯
          ),


     [LAYER_POINTER] = LAYOUT(
     // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          _______,  _______, _______, _______, _______, _______,   _______, _______, _______, _______,  _______, _______,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          _______, _______, _______, _______, _______, _______,  _______, KC_BTN1, KC_BTN3, KC_BTN2, SNIPING, _______,
     // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          _______, _______, _______, _______, _______, _______,    KC_BTN3, KC_BTN1, DRGSCRL, KC_BTN2, SNIPING, _______,
     // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   _______, _______, _______,    _______, _______
     //                            ╰───────────────────────────╯ ╰──────────────────╯
     ),
};
// clang-format on

void keyboard_post_init_user(void) {
    keyboard_post_init_maccel();
}

static uint16_t custom_trackball_counter = 0;
#define CUSTOM_TRACKBALL_TRIGGER_COUNT 10

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }

     // Volume keys on browse layer
     if (layer_state_is(LAYER_BROWSE)) {
          if (mouse_report.y > 0) {
               custom_trackball_counter++;
               if (custom_trackball_counter >= CUSTOM_TRACKBALL_TRIGGER_COUNT) {
                    if (fake_mod_active) {
                         tap_code(KC_BRID);
                    } else {
                         tap_code(KC_VOLD);
                    }
                    custom_trackball_counter = 0;
               }
          } else if (mouse_report.y < 0) {
               custom_trackball_counter++;
               if (custom_trackball_counter >= CUSTOM_TRACKBALL_TRIGGER_COUNT) {
                    if (fake_mod_active) {
                         tap_code(KC_BRIU);
                    } else {
                         tap_code(KC_VOLU);
                    }
                    custom_trackball_counter = 0;
               }
          }
          mouse_report.y = 0;
          mouse_report.x = 0;
          return mouse_report;
     }

#ifdef MACCEL_ENABLE
    return pointing_device_task_maccel(mouse_report);
#endif

    return mouse_report;
}

#include "print.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
     if (keycode == FAKE_MOD) {
          fake_mod_active = record->event.pressed;
          return false;
     }

     if ((keycode == LGUI_CBS || keycode == BROWSE_CBS) && record->event.pressed) {
          if (record->tap.count && record->event.pressed) {
               tap_code16(C(KC_BSPC));
               return false;
          }
     }

     if (layer_state_is(LAYER_POINTER)) {
          if (keycode != KC_BTN1 && keycode != KC_BTN2 && keycode != KC_BTN3) {
               if (keycode < QK_KB_0) {
                    uprintf("process_record_user: keycode %04X on pointer layer\n", keycode);
                    // if (!IS_MODIFIER_KEYCODE(keycode)) { // mod+mouse is also acceptable // or is it? mod+workspace e.g.
                         auto_pointer_layer_timer = 0;
                         layer_off(LAYER_POINTER); // disable mouse layer if non-mouse key pressed
                    // }
              }
         } else {
              auto_pointer_layer_timer = timer_read(); // reset timer on mouse press
         }
    }

     if (record->event.pressed) {
          uprintf("process_record_user: keycode %04X pressed, mods: %04X\n", keycode, get_mods());
          if ((get_mods() != 0) && (!(get_mods() & MOD_MASK_SHIFT))) {
               uprintf("process_record_user: activating layer LAYER_QWERTY\n");
               layer_on(LAYER_QWERTY);
          } else { // regular other key
              if (layer_state_is(LAYER_QWERTY) && (get_mods() == 0 || get_mods() == MOD_MASK_SHIFT)) {
                   uprintf("process_record_user: deactivating layer LAYER_QWERTY\n");
                   layer_off(LAYER_QWERTY);
              } else if (get_mods() != 0 && get_mods() != 2) {
                   uprintf("process_record_user: [2] activating layer LAYER_QWERTY\n");
                   layer_on(LAYER_QWERTY);
              }
          }
     } else {
          if (get_mods() == 0 || get_mods() == MOD_MASK_SHIFT) {
              layer_off(LAYER_QWERTY);
          }
      }
//     if (get_mods() & ~MOD_MASK_SHIFT) {
//           if (record->event.pressed) {
//                layer_on(LAYER_QWERTY);
//           } else {
//                if ((get_mods() == MOD_MASK_SHIFT) || (get_mods() == 0)) { // Make sure only shift (or nothing) is held
//                     layer_off(LAYER_QWERTY);
//                }
//           }
//     }

    return true;
 }

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
     switch (keycode) {
         case LC_TAB:
             return true; // Immediately select the hold action when another key is pressed.
         case SYM_TAB:
             return true;
         case LGUI_CBS:
         case BROWSE_CBS:
             return true;
         case NAV_SPC:
             return false;
         case SPC_NUM:
             return false;
         default:
             return true;
     }
 }

const key_override_t brightness_up_override = ko_make_basic(MOD_MASK_SHIFT, KC_VOLU, KC_BRIU);
const key_override_t brightness_down_override = ko_make_basic(MOD_MASK_SHIFT, KC_VOLD, KC_BRID);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
     &brightness_up_override,
     &brightness_down_override
};