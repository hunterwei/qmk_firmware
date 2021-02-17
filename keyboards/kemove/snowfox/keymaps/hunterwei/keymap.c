#include <stdint.h>
#include "snowfox.h"

enum kemove_layers {
  _BASE_LAYER,
  _MAC_LAYER,
  _ARROW_LAYER,
  _FN_LAYER,
  _FN2_LAYER,
};

// This is ROW*MATRIX_COLS + COL
#define CAPS_LOCATION (MATRIX_COLS * 2 + 0)

enum custom_keycodes {
    // Macro key declarations
    PASTE_VPN_PASS = SNOWFOX_SAFE_RANGE
};

/* Tap Dance zone */
// Tap Dance enums
enum td_keycodes {
    LALT_OSLFN,
    RALT_TGFN,
};
// Define a type containing as tapdance states as you need
typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    TRIPLE_TAP,
    TRIPLE_HOLD
};


// Declare your tapdance functions:
// Function to determine the current tapdance state
uint8_t cur_dance(qk_tap_dance_state_t *state);
// `finished` and `reset` functions for each tapdance keycode
void lalt_finished(qk_tap_dance_state_t *state, void *user_data);
void lalt_reset(qk_tap_dance_state_t *state, void *user_date);

// /* States & timers */
// uint16_t gui_timer = 0;

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
  * Layer _BASE_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Caps   |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter     |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  LWin |TD_LAlt|               space             |TD_RAlt|   FN2  | Ctrl |  FN1  |
  * \-----------------------------------------------------------------------------------------/
  * Layer HOLD in _BASE_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
  * |-----------------------------------------------------------------------------------------+
  * |        |     |     |     |     |     |     |     |     |     |     |     |     |        |
  * |-----------------------------------------------------------------------------------------+
  * |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
  * |-----------------------------------------------------------------------------------------+
  * |            |     |     |     |     |     |     |     |     |     |     |                |
  * |-----------------------------------------------------------------------------------------+
  * |       |       |       |             Arrow_L             |       |       |       |  FN_L |
  * \-----------------------------------------------------------------------------------------/
  */
  [_BASE_LAYER] = KEYMAP( /* Base */
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,   KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,  KC_BSLS,
    LT(_FN_LAYER, KC_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,         KC_ENT,
    KC_LSFT,KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_UP),
    KC_LCTL,KC_LGUI,TD(LALT_OSLFN),LT(_ARROW_LAYER, KC_SPC),TD(RALT_TGFN),LT(_FN2_LAYER, KC_LEFT),RCTL_T(KC_DOWN),LT(_FN_LAYER, KC_RIGHT)
  ),
  /*
  * Layer _MAC_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  Alt  |  L1   |               space             |  Alt  |  FN1  |  R1   | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  * Layer HOLD in _MAC_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
  * |-----------------------------------------------------------------------------------------+
  * |        |     |     |     |     |     |     |     |     |     |     |     |     |        |
  * |-----------------------------------------------------------------------------------------+
  * | Arrow_L |     |     |     |     |     |     |     |     |     |     |     |             |
  * |-----------------------------------------------------------------------------------------+
  * |            |     |     |     |     |     |     |     |     |     |     |                |
  * |-----------------------------------------------------------------------------------------+
  * |       |       |       |                                 |       | FN_L  |       |       |
  * \-----------------------------------------------------------------------------------------/
  */
  [_MAC_LAYER] = KEYMAP( /* Base */
    KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,   KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,  KC_BSLS,
    LT(_ARROW_LAYER, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,         KC_ENT,
    KC_LSFT,KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
    KC_LCTL,KC_LALT, KC_LGUI,      KC_SPC,             KC_RALT,  MO(_FN_LAYER),  KC_RGUI, KC_RCTL
  ),
  /* Layer _ARROW_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |Alt+F1|     |     |Ctl+F4|     |     |     |     |     |Home|Ctl+P-|Ctl+P+|   Del  |
  * |-----------------------------------------------------------------------------------------+
  * | CS+Tab |     |NextWd|    |PgUp|    |     |PrevWd|NextWd|     |     |     |     |   Ins  |
  * |-----------------------------------------------------------------------------------------+
  * |         |     |CAS+In|     |PgDn|     | <-  | \/  |  ^  | ->  |     |     |             |
  * |-----------------------------------------------------------------------------------------+
  * |            |     |     |Ctl+C|CAS+V|PrevWd| Home | End |     |SplitR|SplitD|            |
  * |-----------------------------------------------------------------------------------------+
  * |       |       |       |                                 |       |       |       |       |
  * \-----------------------------------------------------------------------------------------/
  */
  [_ARROW_LAYER] = KEYMAP( /* Base */
    KC_GRAVE, LALT(KC_F1), KC_TRNS, KC_TRNS, LCTL(KC_F4), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, LCTL(KC_PMNS), LCTL(KC_PPLS), KC_DEL,
    LCTL(LSFT(KC_TAB)), KC_TRNS, LCTL(KC_RIGHT), KC_TRNS, KC_PGUP, KC_TRNS, KC_TRNS, LCTL(KC_LEFT), LCTL(KC_RIGHT), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_INS,
    KC_TRNS, KC_TRNS, LCTL(LALT(LSFT(KC_INS))), KC_TRNS, KC_PGDN, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_TRNS, KC_PGDN,         KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, LCTL(KC_C), LCTL(LALT(LSFT(KC_V))), LCTL(KC_LEFT), KC_HOME, KC_END, KC_TRNS, LCTL(LALT(LSFT(KC_DOT))), LCTL(LALT(LSFT(KC_COMM))), KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,             KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS
  ),
  /* Layer _FN_LAYER (Functions + Mouse Keys)
  * ,-----------------------------------------------------------------------------------------.
  * |  ~  | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |           |
  * |-----------------------------------------------------------------------------------------+
  * |  Esc   | BT1 | BT2 | BT3 |     |     |     |LClick| ^ |RClick|Macro1|Home| End |  Ins   |
  * |-----------------------------------------------------------------------------------------+
  * |      |LClick|RClick|    |    |    |LScroll| <-  | \/ | ->  |RScroll|      |      |      |
  * |-----------------------------------------------------------------------------------------+
  * |  LShift  |     |     |     |     |     |UScroll|DScroll|     |    |    |                |
  * |-----------------------------------------------------------------------------------------+
  * | LCtrl |       |  LALT |                                 |TD_RALT| MAC_L |      | BASE_L |
  * \-----------------------------------------------------------------------------------------/
  */
  [_FN_LAYER] = KEYMAP( /* Base */
    KC_TILD, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,   KC_TRNS,
    KC_ESC, SNOWFOX_BLE_DISCOVER, SNOWFOX_BLE_CONN, SNOWFOX_BLE_DISCONN, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2, PASTE_VPN_PASS, KC_HOME, KC_END, KC_INS,
    KC_TRNS, KC_MS_BTN1, KC_MS_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_WH_LEFT, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_WH_RIGHT, KC_TRNS, KC_TRNS,
    KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_WH_UP, KC_MS_WH_DOWN, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSFT,
    KC_LCTL, KC_TRNS, KC_LALT,      KC_TRNS,             TD(RALT_TGFN), DF(_MAC_LAYER), KC_RCTL, DF(_BASE_LAYER)
  ),
  /* Layer _FN2_LAYER (Macros + Misc + Lighting)
  * ,-----------------------------------------------------------------------------------------.
  * |    |BT_DISC|BT_CON|BT_DIS|   |    |    |     |     |     |     |LED_BDN|LED_BUP| LED_Off|
  * |-----------------------------------------------------------------------------------------+
  * |        |     |     |     |     |     |     |     |     |     |Macro1|    |LED_Nxt|LED_On|
  * |-----------------------------------------------------------------------------------------+
  * |      |    |     |     |     |     |      |      |     |     |      |      |             |
  * |-----------------------------------------------------------------------------------------+
  * |         |     |     |     |     |     |     |      |     |     |     |                  |
  * |-----------------------------------------------------------------------------------------+
  * |       |C+A+Del|       |                                 |       |       |      |        |
  * \-----------------------------------------------------------------------------------------/
  */
  [_FN2_LAYER] = KEYMAP( /* Base */
    KC_TRNS, SNOWFOX_BLE_DISCOVER, SNOWFOX_BLE_CONN, SNOWFOX_BLE_DISCONN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, SNOWFOX_LED_BDN, SNOWFOX_LED_BUP, SNOWFOX_LED_OFF,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, PASTE_VPN_PASS, KC_TRNS, SNOWFOX_LED_NEXT, SNOWFOX_LED_ON,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, LCTL(LALT(KC_DEL)), KC_TRNS,      KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
};

const uint16_t keymaps_size = sizeof(keymaps);

void dip_switch_update_user(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        layer_on(_MAC_LAYER);
      } else {
        layer_off(_MAC_LAYER);
      }
      break;
  }
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

layer_state_t layer_state_set_user(layer_state_t layer) {
    return layer;
}

bool led_update_user(led_t leds) {
  return true;
}

/* Tap Dance functions */
// Determine the tapdance state to return
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted || !state->pressed) return DOUBLE_TAP;
        else return DOUBLE_HOLD;
    } else if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8; // Magic number. At some point this method will expand to work for more presses
}

static tap lalt_tap_state = {
    .is_press_action = true,
    .state = 0
};

// Handle the possible states for each tapdance keycode you define:
void lalt_finished(qk_tap_dance_state_t *state, void *user_data) {
    lalt_tap_state.state = cur_dance(state);
    switch(lalt_tap_state.state) {
        case SINGLE_TAP:
            set_oneshot_layer(_FN_LAYER, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case SINGLE_HOLD:
            register_code(KC_LALT);
            break;
        case DOUBLE_TAP:
            // do nothing
            break;
        case DOUBLE_HOLD:
            // do nothing
            break;
        case TRIPLE_TAP:
            // do nothing
            break;
        case TRIPLE_HOLD:
            // do nothing
            break;
    }
}

void lalt_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch(lalt_tap_state.state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LALT);
            break;
        case DOUBLE_TAP:
            // do nothing
            break;
        case DOUBLE_HOLD:
            // do nothing
            break;
        case TRIPLE_TAP:
            // do nothing
            break;
        case TRIPLE_HOLD:
            // do nothing
            break;
    }
    lalt_tap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [LALT_OSLFN] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, lalt_finished, lalt_reset, 175),
    [RALT_TGFN] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_RALT, _FN_LAYER)
};

/* User customized keycode handlers */
bool process_record_user (uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_TRNS:
        case KC_NO:
            // Always cancel one-shot layer when another key gets pressed
            if (record -> event.pressed && is_oneshot_layer_active())
            clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            break;
        case PASTE_VPN_PASS:
            if (record->event.pressed) {
                // when keycode PASTE_VPN_PASS is pressed
                SEND_STRING("1474" SS_LCTL("v") SS_TAP(X_ENT) SS_DELAY(3500) SS_TAP(X_ENT));
            } else {
                // when keycod PASTE_VPN_PASS is released
            }
            break;
    }
    return true;
};
