/* Copyright 2021 bdtc123
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_ansi(
        QK_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        _______,   KC_LCTL,   KC_LALT,                       KC_SPC,                              KC_RALT,  MO(1),  KC_RCTL,       _______
    ),
    [1] = LAYOUT_60_ansi(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  QK_BOOT,
        _______,     KC_PGUP, KC_UP, KC_PGDN, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, _______, KC_PSCR, _______, _______, _______,
        _______,       KC_LEFT,  KC_DOWN,  KC_RIGHT,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_SPD,  _______, _______, _______, _______, RGB_MOD,
        _______,            _______, _______, _______, _______, _______, _______, NK_TOGG, KC_END, KC_INS, KC_DEL, _______,
        _______,   _______,   _______,                      RGB_TOG,                              _______,   _______,   KC_RGUI,   _______
    ),

};

bool led_update_user(led_t led_state) {
    
    static uint8_t c = 0; 
    static bool f = false;
    static uint8_t RGB_current_mode;
    static uint8_t RGB_current_hue;
    static uint8_t RGB_current_sat;
    static uint8_t RGB_current_val;

    if (!c && led_state.caps_lock) { // капс включился
        if (rgb_matrix_get_val()) {
            RGB_current_mode = rgblight_get_mode();
            RGB_current_hue = rgblight_get_hue();
            RGB_current_sat = rgblight_get_sat();
            RGB_current_val = rgblight_get_val();
            rgblight_sethsv(HSV_PINK);
            rgblight_mode(1);
            f = true;
        } else {
            rgblight_sethsv(rgb_matrix_get_hue(), rgb_matrix_get_sat(), 180);
        }
    }
    if (c && !led_state.caps_lock) { //капс выключился
            if (f) {
                rgblight_mode(RGB_current_mode);
                rgblight_sethsv(RGB_current_hue, RGB_current_sat, RGB_current_val);
                f = false;
            } else {
                rgblight_sethsv(rgb_matrix_get_hue(), rgb_matrix_get_sat(), 0);
            }
    }
        c = led_state.caps_lock;
        return true;
    } 

