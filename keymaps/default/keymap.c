#include QMK_KEYBOARD_H

// Define the keycode, `QK_USER` avoids collisions with existing keycodes
enum keycodes {
  KC_CYCLE_LAYERS = QK_USER,
};

// 1st layer on the cycle
#define LAYER_CYCLE_START 0
// Last layer on the cycle
#define LAYER_CYCLE_END   2


#define L_BASE 2
#define L_YOUTUBE 1
#define L_MOUSE 0
// F3603D,
// F360SK,
// CODE,
// TERM,

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_BASE] = LAYOUT_ortho_4x3(
        KC_1, KC_2, KC_3,
        KC_4, KC_5, KC_6,
        KC_7, KC_8, KC_9,
        KC_NO, KC_NO, KC_CYCLE_LAYERS
    ),
    [L_YOUTUBE] = LAYOUT_ortho_4x3(
        KC_1, KC_M, KC_C,
        KC_J, KC_K, KC_L,
        KC_7, KC_I, KC_F,
        KC_NO, KC_NO, KC_CYCLE_LAYERS
    ),
    [L_MOUSE] = LAYOUT_ortho_4x3(
        KC_BTN1, KC_BTN3, KC_BTN2,
        KC_WH_D, KC_MS_U , KC_WH_U,
        KC_MS_L, KC_MS_D, KC_MS_R,
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

    // Process other keycodes normally
    default:
      return true;
  }
}

// Place `KC_CYCLE_LAYERS` as a keycode in your keymap

#ifdef OLED_ENABLE

bool oled_task_user(void) {
    switch (get_highest_layer(layer_state)) {
        case L_BASE:
            oled_write_P(PSTR("BASE\n"), false);
            break;
        case L_YOUTUBE:
            oled_write_P(PSTR("YOUTUBE\n"), false);
            break;
        case L_MOUSE:
            oled_write_P(PSTR("MOUSE\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    return false;
}
#endif

