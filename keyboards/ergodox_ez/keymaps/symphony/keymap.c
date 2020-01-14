#include QMK_KEYBOARD_H
#include "version.h"

// Layer Definitions
#define ROOT 0 // root
#define TEST 1 // media keys and mouse
#define SYMB 2 // symbols
#define NAVI 3 // text navigation
#define APPL 4 // media keys and mouse


// Tap-Dance Definitions
#define TD_SWITCH 0
#define TD_CPY_CUT 1
#define TD_BCK_FWD 2
#define TD_NXT_PRV 3

// Custom Keycodes Definitions
enum custom_keycodes {
#ifdef ORYX_CONFIGURATOR
  EPRM = EZ_SAFE_RANGE,
#else
  EPRM = SAFE_RANGE,
#endif
  VRSN,
  RGB_SLD
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Alt+Tab, Shift+Alt+Tab
  [TD_SWITCH] = ACTION_TAP_DANCE_DOUBLE(A(KC_TAB), C(A(KC_TAB))),
  [TD_CPY_CUT] = ACTION_TAP_DANCE_DOUBLE(C(KC_C), C(KC_X)),
  [TD_BCK_FWD] = ACTION_TAP_DANCE_DOUBLE(A(KC_LEFT), A(KC_RGHT)),
  [TD_NXT_PRV] = ACTION_TAP_DANCE_DOUBLE(KC_MNXT, KC_MPRV)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/* Keymap 0: Root layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Escape |      |      |      |      |      |      |           |      |      |      |      |      |      |   ⊞   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Caps  |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |    \   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    =   |   A  |   S  | D_Alt|F_Ctrl|G_Shft|------|           |------|   H  |J_Shft|K_Ctrl| L_Alt|   ;  |    '   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  TEST  |   /  |   Z  |   X  |   C  |   V  |      |           |      |   B  |   N  |   M  |   ,  |   .  |    -   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      | Undo | Redo |CpyCut| Paste|                                       | Prev | Ahead|BckFwd|Switch|      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |Backsp|Delete|------|       |------| Enter| Space|
 *                                 | _NAVI| _SYMB| App  |       |  Tab |      | _APPL|
 *                                 `--------------------'       `--------------------'
 */
[ROOT] = LAYOUT_ergodox(
  KC_ESC,   KC_NO,   KC_NO,       KC_NO,          KC_NO,       KC_NO, KC_NO,
  KC_CAPS,  KC_Q,    KC_W,        KC_E,           KC_R,        KC_T,  KC_NO,
  KC_EQL,   KC_A,    ALT_T(KC_S), CTL_T(KC_D),    SFT_T(KC_F), KC_G,
  TG(TEST), KC_SLSH, KC_Z,        KC_X,           KC_C,        KC_V,  KC_NO,
  KC_NO,    C(KC_Z), C(S(KC_Z)),  TD(TD_CPY_CUT), C(KC_V),
                                                              KC_NO,  KC_NO,
                                                                      KC_NO,
                                LT(NAVI, KC_BSPC), LT(SYMB, KC_DEL), KC_APP,

  KC_NO,     KC_NO,       KC_NO,          KC_NO,         KC_NO,        KC_NO,   KC_LWIN,
  KC_NO,     KC_Y,        KC_U,           KC_I,          KC_O,         KC_P,    KC_BSLS,
             KC_H,        RSFT_T(KC_J),   RCTL_T(KC_K),  RALT_T(KC_L), KC_SCLN, KC_QUOT,
  KC_NO,     KC_B,        KC_N,           KC_M,          KC_COMM,      KC_DOT,  KC_MINS, 
  C(KC_TAB), C(S(KC_TAB)), TD(TD_BCK_FWD), TD(TD_SWITCH), KC_NO,
  KC_NO, KC_NO,
  KC_NO,
  KC_TAB, KC_ENT, LT(APPL, KC_SPC)
),  
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/* Keymap 0: Testing layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Escape |      |      |      |      |      |      |           |      |      |      |      |      |      |   ⊞   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Caps  |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |    \   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    =   |   A  |   S  | D_Alt|F_Ctrl|G_Shft|------|           |------|   H  |J_Shft|K_Ctrl| L_Alt|   ;  |    '   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  |    -   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      | Undo | Redo |CpyCut| Paste|                                       | Prev | Ahead|BckFwd|Switch|      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |Backsp|Delete|------|       |------| Enter| Space|
 *                                 | _NAVI| _SYMB| App  |       |  Tab |      | _APPL|
 *                                 `--------------------'       `--------------------'
 */
[TEST] = LAYOUT_ergodox(
  KC_ESC,   KC_NO,   KC_NO,       KC_NO,          KC_NO,       KC_NO, KC_NO,
  KC_CAPS,  KC_Q,    KC_W,        KC_E,           KC_R,        KC_T,  KC_NO,
  KC_EQL,   KC_A,    ALT_T(KC_S), CTL_T(KC_D),    SFT_T(KC_F), KC_G,
  TG(TEST), KC_Z,    KC_X,        KC_C,           KC_V,        KC_B,  KC_NO,
  KC_NO,    C(KC_Z), C(S(KC_Z)),  TD(TD_CPY_CUT), C(KC_V),
                                                          KC_NO,  KC_NO,
                                                                  KC_NO,
                            LT(NAVI, KC_BSPC), LT(SYMB, KC_DEL), KC_APP,

  KC_NO,     KC_NO,       KC_NO,          KC_NO,         KC_NO,        KC_NO,   KC_LWIN,
  KC_NO,     KC_Y,        KC_U,           KC_I,          KC_O,         KC_P,    KC_BSLS,
             KC_H,        RSFT_T(KC_J),   RCTL_T(KC_K),  RALT_T(KC_L), KC_SCLN, KC_QUOT,
  KC_NO,     KC_N,        KC_M,           KC_COMM,       KC_DOT,       KC_SLSH, KC_MINS, 
  C(KC_TAB), C(S(KC_TAB)), TD(TD_BCK_FWD), TD(TD_SWITCH), KC_NO,
  KC_NO, KC_NO,
  KC_NO,
  KC_TAB, KC_ENT, LT(APPL, KC_SPC)
),
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYMB] = LAYOUT_ergodox(
  VRSN,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
  KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS,
  KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,
  KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,
  EPRM,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,

  KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_TRNS, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
  KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_TRNS,
  KC_TRNS, KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, KC_TRNS,
  KC_0,    KC_DOT,  KC_TRNS, KC_EQL,  KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS
),
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/* Keymap 2: Text navigation layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[NAVI] = LAYOUT_ergodox(
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,

  KC_TRNS,       KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
  C(S(KC_UP)),   KC_TRNS,    KC_HOME, KC_UP,   KC_END,  KC_TRNS,    KC_TRNS,
                 C(KC_LEFT), KC_LEFT, KC_DOWN, KC_RGHT, C(KC_RGHT), KC_TRNS,
  C(S(KC_DOWN)), KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS
),
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      | WhUp |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |WhLeft|WhDown|WhRght|      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |MsSpd1|MsSpd2|MsSpd3|      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |VolDn |VolUp | Mute |NxtPrv|      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      | Reset|
 *                                 ,------|------|------|       |------+------+------.
 *                                 | Left | Right|      |       |      |      |      |
 *                                 | Click| Click|------|       |------|      |      |
 *                                 |      |      |MClick|       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[APPL] = LAYOUT_ergodox(
  // left hand
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                               KC_TRNS, KC_TRNS,  
                                                        KC_TRNS,
                                      KC_BTN1, KC_BTN2, KC_BTN3,
  // right hand
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_U, KC_TRNS, KC_TRNS,        KC_TRNS,
           KC_TRNS, KC_WH_L, KC_WH_D, KC_WH_R, KC_TRNS,        KC_MPLY,
  KC_TRNS, KC_TRNS, KC_ACL0, KC_ACL1, KC_ACL2, KC_TRNS,        KC_TRNS,
                    KC_VOLD, KC_VOLU, KC_MUTE, TD(TD_NXT_PRV), KC_TRNS,
  KC_TRNS, RESET,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_WBAK
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case EPRM:
        eeconfig_init();
        return false;
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      #ifdef RGBLIGHT_ENABLE
      case RGB_SLD:
        rgblight_mode(1);
        return false;
      #endif
    }
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = get_highest_layer(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};

uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case SFT_T(KC_F):
      return 140; 
    case RSFT_T(KC_J):
      return 100;
    default:
      return TAPPING_TERM;
  }
}

// /*********************************************************************************************************************/
// /*********************************************************************************************************************/
// /* Keymap 2: Text navigation layer
//  *
//  * ,--------------------------------------------------.           ,--------------------------------------------------.
//  * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
//  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
//  * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
//  * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
//  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
//  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
//  *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
//  *   `----------------------------------'                                       `----------------------------------'
//  *                                        ,-------------.       ,-------------.
//  *                                        |      |      |       |      |      |
//  *                                 ,------|------|------|       |------+------+------.
//  *                                 |      |      |      |       |      |      |Brwser|
//  *                                 |      |      |------|       |------|      |Back  |
//  *                                 |      |      |      |       |      |      |      |
//  *                                 `--------------------'       `--------------------'
//  */
// [MDIA] = LAYOUT_ergodox(
//   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//                                                KC_TRNS, KC_TRNS,
//                                                         KC_TRNS,
//                                       KC_TRNS, KC_TRNS, KC_TRNS,

//   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//   KC_TRNS, KC_TRNS,
//   KC_TRNS,
//   KC_TRNS, KC_TRNS, KC_TRNS
// ),