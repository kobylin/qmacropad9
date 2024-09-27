#include QMK_KEYBOARD_H

// Define the keycode, `QK_USER` avoids collisions with existing keycodes
enum keycodes {
    KC_CYCLE_LAYERS = QK_USER,
    KC_SWITCH_LANG,
    KC_BROWSER_UNDOTAB,
    KC_TERM_FIND,
};

// 1st layer on the cycle
#define LAYER_CYCLE_START 0
// Last layer on the cycle
#define LAYER_CYCLE_END   3


#define L_BASE 0
#define L_YOUTUBE 1
#define L_MOUSE 2
#define L_CODE 3
// F3603D,
// F360SK,
// TERM,

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_BASE] = LAYOUT_ortho_4x3(
        KC_1, KC_2, KC_3,
        KC_4, KC_5, KC_6,
        KC_7, KC_8, KC_9,
        KC_NO, KC_NO, KC_CYCLE_LAYERS
    ),
    [L_YOUTUBE] = LAYOUT_ortho_4x3(
        LGUI(KC_W), KC_BROWSER_UNDOTAB, LCTL(KC_TAB),
        KC_LEFT, KC_SPACE, KC_RIGHT,
        KC_I, KC_C, KC_F,
        KC_NO, KC_NO, KC_CYCLE_LAYERS
    ),
    [L_MOUSE] = LAYOUT_ortho_4x3(
        KC_BTN1, KC_MS_U, KC_BTN2,
        KC_MS_L, KC_MS_D, KC_MS_R,
        KC_BTN3, KC_WH_D, KC_WH_U,
        KC_NO, KC_NO, KC_CYCLE_LAYERS
    ),
    [L_CODE] = LAYOUT_ortho_4x3(
        KC_ESC, KC_SWITCH_LANG, KC_D,
        KC_I, KC_K, KC_O,
        KC_H, KC_J, KC_L,
        KC_NO, KC_NO, KC_CYCLE_LAYERS
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case L_YOUTUBE:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        case L_MOUSE:
            if (clockwise) {
                tap_code(KC_WH_U);
            } else {
                tap_code(KC_WH_D);
            }
            break;
        case L_CODE:
            if (clockwise) {
                tap_code(KC_DOWN);
            } else {
                tap_code(KC_UP);
            }
            break;
        default:
            return false;
    }
    return false;
}

// Add the behaviour of this new keycode
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_CYCLE_LAYERS:
      // Our logic will happen on presses, nothing is done on releases
      if (!record->event.pressed) {
        // We've already handled the keycode (doing nothing), let QMK know so no further code is run unnecessarily
        return false;
      }

      uint8_t current_layer = get_highest_layer(layer_state);

      // Check if we are within the range, if not quit
      if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) {
        return false;
      }

      uint8_t next_layer = current_layer + 1;
      if (next_layer > LAYER_CYCLE_END) {
          next_layer = LAYER_CYCLE_START;
      }
      layer_move(next_layer);
      return false;

    case KC_SWITCH_LANG:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            wait_ms(20);
            tap_code(KC_SPACE);
            wait_ms(20);
            unregister_code(KC_LCTL);
        }
        return false;

    case KC_BROWSER_UNDOTAB:
        if (record->event.pressed) {
            register_code(KC_LGUI);
            register_code(KC_LSFT);
            wait_ms(20);
            tap_code(KC_T);
            wait_ms(20);
            unregister_code(KC_LGUI);
            unregister_code(KC_LSFT);
        }
        return false;

    // Process other keycodes normally
    default:
      return true;
  }
}


#ifdef OLED_ENABLE

// static void render_qmk_logo(void) {
//   static const char PROGMEM qmk_logo[] = {
//     0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
//     0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
//     0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
//
//     oled_write_P(qmk_logo, true);
// }

static void render_uaqmk_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,252, 24, 48,224,128,  0,  0,  0,  0,254,  0,  0,  0,  0,192,224, 48, 24,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128,128,128,  0,  0,  0,  0,128,128,128,  0,  0,  0,  0,128,128,128,  0,  0,  0,128,128,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,  0,  0,  0,  3,254,  0,  0,192,255,192,  0,  0,254,  3,  0,  0,  0,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,  1,  1,  1,255,255,240,  0,  0,255,255, 31,254,128,128,252, 63,255,255,  0,  0,  0,255,255,224,248, 30,  7,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,  4,  4, 10, 17,240, 24, 38, 67,128, 67, 38, 24,240, 17, 10,  4,  4,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,127, 96,124,252,255, 63,  3,  0,  0,255,255,  0,  7, 31, 31,  7,  0,255,255,  0,  0,  0,255,255,  1,  7, 31,252,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  1,  1,  1,  1,  1,  7, 25, 33, 65,255, 65, 33, 25,  7,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void render_yt_logo(void) {
    static const char PROGMEM raw_logo[] = {
 0,  0,  0,  0,  0,  0,  0,  0,  0,224,240,248,252,254,254,254,254,254,254,254,254,254,254, 14, 14, 30, 62,126,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,252,248,240,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24, 60,124,248,240,224,192,128,  0,  0,  0,  0,128,192,224,240,248,124, 60, 24,  0,  0,  0,  0, 60, 60, 60, 60, 60, 60, 60, 60,252,252,252,252, 60, 60, 60, 60, 60, 60, 60, 60,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15, 31, 63,127,255,255,255,255,255,255,255,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15,255,254,254,255, 15,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  0,  0,  0,  0,  0,  0,128,192,224,240,248,252,254,255,255,255,255,255,255,255,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 15, 31, 63,127,127,127,127,127,127,127,127,127,127,112,112,120,124,126,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127, 63, 31, 15,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 15, 15, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 15, 15, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,

    };

    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void render_mouse_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,128, 64, 64, 64, 64, 64, 64,248, 68, 67, 64, 64, 64, 64,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,254,  1,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,  0,  0,  0,  0,  1,254,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,255,  1,  2,  2,  2,  2,  2,  2,  2,  3,  2,  2,  2,  2,  2,  2,  2,  1,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0, 15, 16, 32, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 32, 16, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };

    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void render_code_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,254,  2,  2,186,186,186,130,130, 58, 58,186,186,130,130,186, 58, 58,130,130,186,186,186,  2,  2,186,186,186,130,130, 58, 58,186,130,130,186,186,186,130,130,186,186,186,  2,  2,254,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,207, 72, 72, 72, 79, 64,192, 15,  8,200, 72, 79, 64, 64,207,  8,  8,200, 79, 64, 64,207,  8,  8,200, 79, 64, 64,207,  8,  8,  8,  8,  8,232,232,232,232,239,  0,  0,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,207, 72, 72, 72,200,  8, 15,192, 64, 79, 72, 72, 72, 72, 79, 64, 64, 79, 72, 72, 72, 79, 64, 64, 79, 72, 72, 72, 79, 64, 64,207, 15, 13,205, 77, 76, 79,207,  0,  0,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0, 63, 32, 32, 39, 36, 36, 36, 39, 32, 32, 39, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 39, 32, 32, 39, 36, 36, 36, 39, 32, 32, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

bool oled_task_user(void) {
    int8_t current_layer = get_highest_layer(layer_state);

    switch (current_layer) {
        case L_BASE:
            render_uaqmk_logo();
            break;
        case L_YOUTUBE:
            render_yt_logo();
            // oled_write_P(PSTR("YT\n"), false);
            break;
        case L_MOUSE:
            render_mouse_logo();
            // oled_write_P(PSTR("MOUSE\n"), false);
            break;
        case L_CODE:
            render_code_logo();
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    return false;
}

#endif

