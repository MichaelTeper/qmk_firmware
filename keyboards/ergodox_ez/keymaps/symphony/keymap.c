#include QMK_KEYBOARD_H
#include "version.h"

// Layer Definitions
#define ROOT 0 // root
#define PASS 1 // pass
#define SYMB 2 // symbols
#define NAVI 3 // text navigation
#define APPL 4 // media keys and mouse
#define WIND 5 // Window

// Custom Keycodes Definitions
enum custom_keycodes {
#ifdef ORYX_CONFIGURATOR
  EPRM = EZ_SAFE_RANGE,
#else
  EPRM = SAFE_RANGE,
#endif
  VRSN,
  RGB_SLD,
  CU_MINI,
  CU_MAXI,
  CU_ATAB,
  CU_LLCK,
};

#define SY_F SFT_T(KC_F)
#define SY_D CTL_T(KC_D)
#define SY_S ALT_T(KC_S)
#define SY_J RSFT_T(KC_J)
#define SY_K RCTL_T(KC_K)
#define SY_L RALT_T(KC_L)
#define SY_COPY TD(TD_CPY_CUT)
#define SY_ENT LT(WIND, KC_ENT)
#define SY_BSPC LT(NAVI, KC_BSPC)
#define SY_DEL LT(SYMB, KC_DEL)
#define SY_SPC LT(APPL, KC_SPC)
#define SY_FOLD C(S(KC_LBRC))
#define SY_UFLD C(S(KC_RBRC))

//Variables
bool alt_tab_active = false;
bool caps_locked = false;
bool layer_locked = false;
uint16_t blink_timer = 0;
bool blink = false;

//Tap Dance Definitions
#define TD_CPY_CUT 0
#define TD_BCK_FWD 1
#define TD_NXT_PRV 2

qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Alt+Tab, Shift+Alt+Tab
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
 * | Escape |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   ⊞   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Caps  |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |    \   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    =   |   A  |   S  | D_Alt|F_Ctrl|G_Shft|------|           |------|   H  |J_Shft|K_Ctrl| L_Alt|   ;  |    '   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  TEST  |   /  |   Z  |   X  |   C  |   V  |      |           |      |   B  |   N  |   M  |   ,  |   .  |    -   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Stick| Undo | Redo |CpyCut| Paste|                                       | Prev | Ahead|BckFwd|Switch| Stick|
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
  KC_ESC,   KC_F1,   KC_F2,      KC_F3,   KC_F4,   KC_F5, KC_F6,
  KC_CAPS,  KC_Q,    KC_W,       KC_E,    KC_R,    KC_T,  KC_NO,
  KC_EQL,   KC_A,    SY_S,       SY_D,    SY_F,    KC_G,
  TG(PASS), KC_SLSH, KC_Z,       KC_X,    KC_C,    KC_V,  KC_NO,
  CU_LLCK,  C(KC_Z), C(S(KC_Z)), SY_COPY, C(KC_V),
                                                  KC_NO,  KC_NO,
                                                          KC_NO,
                                        SY_BSPC, SY_DEL, KC_APP,

  KC_F7,     KC_F8,        KC_F9,          KC_F10,  KC_F11,  KC_F12,  KC_LWIN,
  KC_NO,     KC_Y,         KC_U,           KC_I,    KC_O,    KC_P,    KC_BSLS,
             KC_H,         SY_J,           SY_K,    SY_L,    KC_SCLN, KC_QUOT,
  KC_NO,     KC_B,         KC_N,           KC_M,    KC_COMM, KC_DOT,  KC_MINS, 
  C(KC_TAB), C(S(KC_TAB)), TD(TD_BCK_FWD), CU_ATAB, CU_LLCK,
  KC_NO, KC_NO,
  KC_NO,
  KC_TAB, SY_ENT, SY_SPC
),  
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/* Keymap 1: Test
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |  Up  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      | Ctrl | Shift|      |------|           |------| WLeft| Left | Down | Right|WRight|        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[PASS] = LAYOUT_ergodox(
  KC_NO,    KC_1,  KC_2,  KC_3,  KC_4,    KC_NO, KC_NO,
  KC_NO,    KC_Q,  KC_W,  KC_E,  KC_R,    KC_NO, KC_NO,
  KC_NO,    KC_A,  KC_S,  KC_D,  KC_F,    KC_NO,
  TG(PASS), KC_NO, KC_NO, KC_NO, S(KC_V), KC_V,  KC_NO,
  KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO,
                                          KC_NO, KC_NO,
                                                 KC_NO,
                                 KC_BSPC, KC_NO, KC_NO,

  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,    KC_NO,
  KC_NO, KC_NO, KC_U,  KC_I,  KC_O,  KC_P,    KC_NO,
         KC_NO, KC_J,  KC_K,  KC_L,  KC_SCLN, KC_NO,
  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,
                KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,
  KC_NO, KC_NO,
  KC_NO,
  KC_NO, KC_NO, KC_ENT
),
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/* Keymap 2: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   !  |   7  |   8  |   9  |   *  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------|   |  |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   .  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |   0  |    . |      |   =  |      |
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
  VRSN,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS,
  KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,
  KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,

  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_EXLM, KC_7,    KC_8,    KC_9,    KC_ASTR, KC_TRNS,
           KC_PIPE, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_TRNS,
  KC_TRNS, KC_AMPR, KC_1,    KC_2,    KC_3,    KC_DOT,  KC_TRNS,
  KC_0,    KC_DOT,  KC_TRNS, KC_EQL,  KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS
),
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/* Keymap 3: Text navigation layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | Fold |UnFold|      |      |           |Cursor|      | Home |  Up  |  End |      |        |
 * |--------+------+------+------+------+------|      |           | Above|------+------+------+------+------+--------|
 * |        |      |      | Ctrl | Shift|      |------|           |------| WLeft| Left | Down | Right|WRight|        |
 * |--------+------+------+------+------+------|      |           |Cursor|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           | Below|      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
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
  KC_TRNS, KC_TRNS, KC_TRNS, SY_FOLD, SY_UFLD, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_LCTL, KC_LSFT, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,

  KC_TRNS,       KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
  C(S(KC_UP)),   KC_TRNS,    KC_HOME, KC_UP,   KC_END,  KC_TRNS,    KC_TRNS,
                 C(KC_LEFT), KC_LEFT, KC_DOWN, KC_RGHT, C(KC_RGHT), KC_TRNS,
  C(S(KC_DOWN)), KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS
),
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/* Keymap 4: Media and mouse key
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |Bar 1 |Bar 2 |Bar 3 |Bar 4 |Bar 5 |Close |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      | WhUp |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |WhLeft|WhDown|WhRght|      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |MsSpd1|MsSpd2|MsSpd3|      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |VolDn |VolUp | Mute |NxtPrv|      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       | Debug| Reset|
 *                                 ,------|------|------|       |------+------+------.
 *                                 | Left | Right|      |       |      |      |      |
 *                                 | Click| Click|------|       |------|      |      |
 *                                 |      |      |MClick|       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[APPL] = LAYOUT_ergodox(
  // left hand
  KC_TRNS, LWIN(KC_1), LWIN(KC_2), LWIN(KC_3), LWIN(KC_4), LWIN(KC_5), KC_TRNS,
  KC_TRNS, KC_TRNS,    KC_TRNS,    KC_MS_U,    KC_TRNS,    KC_TRNS,    KC_TRNS,
  KC_TRNS, KC_TRNS,    KC_MS_L,    KC_MS_D,    KC_MS_R,    KC_TRNS,
  KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
  KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
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
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/* Keymap 5: Window layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |  ⬓  |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |  ❒  |      |      |------|           |------|  ←⎚  |  ▂  |  ⎚→ |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[WIND] = LAYOUT_ergodox(
  KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,       LWIN(KC_UP),   C(KC_W),        KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, LWIN(KC_LEFT), LWIN(KC_DOWN), LWIN(KC_RIGHT), KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,       KC_TRNS,
                                                                  KC_TRNS, KC_TRNS,
                                                                           KC_TRNS,
                                                         KC_TRNS, KC_TRNS, KC_TRNS,
 
  KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,          CU_MAXI, A(KC_F4),         KC_TRNS, KC_TRNS,
           KC_TRNS, S(LWIN(KC_LEFT)), CU_MINI, S(LWIN(KC_RGHT)), KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
                    KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS
),
};

uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case SY_F:
      return 140; 
    case SY_J:
      return 100;
    default:
      return TAPPING_TERM;
  }
} 

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SY_F:
      return true;
    case SY_D:
      return true;
    case SY_S:
      return true;
    case SY_J:
      return true;
    case SY_K:
      return true;
    case SY_L:
      return true;
    case SY_ENT:
      return true;
    case SY_SPC:
      return true;
    default:
      return false;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    //Keycode Extentions
    case KC_CAPS:
      if (record->event.pressed){
        caps_locked = !caps_locked;
        if (!caps_locked) ergodox_right_led_1_off();
      }
      return true;
    case SY_BSPC:
      return !layer_locked;
    case SY_DEL:
      return !layer_locked;
    case SY_SPC :
      return !layer_locked;
    case SY_ENT:
      return !layer_locked;
    //Custom Keycodes
    case CU_LLCK:
      if (record->event.pressed){
        layer_locked = !layer_state_is(ROOT) && !layer_locked;
        if (!layer_locked){
          layer_move(ROOT);
        }
        return false;
      }
    case CU_MINI:
      if (record->event.pressed){
        register_code(KC_LWIN);
        tap_code(KC_DOWN);
        tap_code(KC_DOWN);
        unregister_code(KC_LWIN);
      }
      return false;
    case CU_MAXI:
      if (record->event.pressed){
        register_code(KC_LWIN);
        tap_code(KC_UP);
        tap_code(KC_UP);
        unregister_code(KC_LWIN);
      }
      return false;
    case CU_ATAB:
      if (record->event.pressed){
        if (!alt_tab_active){
          alt_tab_active = true;
          register_code(KC_LALT);
          tap_code(KC_TAB);
        }
      } else {
        alt_tab_active = false;
        unregister_code(KC_LALT);
      }
      return false;
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
        return false;
      }
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      }
    default:
      return true;
  }
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  blink_timer = timer_read();
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

void matrix_scan_user(void) {
  if (timer_elapsed(blink_timer) > 500) {
    blink_timer = timer_read();
    blink = !blink;
    if (caps_locked) {
      blink ? ergodox_right_led_1_on() : ergodox_right_led_1_off();
    }
  }
}

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  if (!caps_locked) ergodox_right_led_1_off();
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



// /*********************************************************************************************************************/
// /*********************************************************************************************************************/
// /* Keymap 0: 
//  *
//  * ,--------------------------------------------------.           ,--------------------------------------------------.
//  * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
//  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
//  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
//  *   |      |      |      |      |      |                                       |      |      |      |      |      |
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