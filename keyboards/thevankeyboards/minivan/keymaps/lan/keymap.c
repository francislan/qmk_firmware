#include QMK_KEYBOARD_H

#define MS_TAB  LT(_MS, KC_TAB)
#define SP_ENT  LT(_SP, KC_ENT)

// Browser tabs manipulation (MacOS)
#define TB_CLS  LCMD(KC_W)
#define TB_NEW  LCMD(KC_T)
#define TB_R    LCTL(KC_TAB)
#define TB_L    LCTL(LSFT(KC_TAB))

// MacOS specific space moving.
#define M_SPC_L LCTL(KC_LEFT)
#define M_SPC_R LCTL(KC_RGHT)

// Tap dance
#define TD_RST TD(TD_RESET)

// Super CMD + TAB: Keeps CMD pressed until the special layer is deactivated.
bool is_cmd_tab_active = false;

enum custom_keycodes {
    CMD_TAB = SAFE_RANGE
};

// Tap dance
enum {
    TD_RESET = 0  // Put into DFU mode after 5 presses.
};

void td_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >= 5) {
        reset_keyboard();
        reset_tap_dance(state);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
   [TD_RESET] = ACTION_TAP_DANCE_FN(td_reset)
};

enum layer_names {
    _MN,  // Main
    _SP,  // Special
    _NB,  // Number
    _FN,  // Function
    _MC,  // Macro
    _MS,  // Mouse
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* 0: Main Layer
    * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬───────┐
    * │ESC │ Q  │ W  │ E  │ R  │ T  │ Y  │ U  │ I  │ O  │ P  │ BACK  │  
    * ├────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬──────┤
    * │↹(MS)│ A  │ S  │ D  │ F  │ G  │ H  │ J  │ K  │ L  │ ;  │ '    │
    * ├─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬────┤
    * │ LSHFT │ Z  │ X  │ C  │ V  │ B  │ N  │ M  │ ,  │ .  │ /  │RSFT│
    * ├────┬──┴─┬──┴─┬──┴─┬──┴────┴──┬─┴────┴──┬─┴───┬┴────┴─┬──┴────┤
    * │LCTL│LALT│(NB)│LCMD│ENTER(SP) │  SPACE  │(NB) │ (MC)  │ (FN)  │
    * └────┴────┴────┴────┴──────────┴─────────┴─────┴───────┴───────┘
    */
    /* 1: Special Layer
    * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬───────┐
    * │ `  │CAPS│TB L│N TB│TB R│    │PGUP│HOME│ UP │END │    │ DEL   │  
    * ├────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬──────┤
    * │     │    │SP_L│APP │SP_R│    │PGDN│LEFT│DOWN│RGHT│ -  │  =   │
    * ├─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬────┤
    * │       │ (  │ )  │CLOS│    │    │    │    │ [  │ ]  │ \  │    │
    * ├────┬──┴─┬──┴─┬──┴─┬──┴────┴──┬─┴────┴──┬─┴───┬┴────┴─┬──┴────┤
    * │    │    │    │    │          │         │     │       │       │
    * └────┴────┴────┴────┴──────────┴─────────┴─────┴───────┴───────┘
    */
    /* 2: Number Layer
    * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬───────┐
    * │    │ 1  │ 2  │ 3  │ 4  │ 5  │ 6  │ 7  │ 8  │ 9  │ 0  │ BACK  │  
    * ├────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬──────┤
    * │     │ +  │ -  │ *  │ /  │ ^  │    │ 4  │ 5  │ 6  │ -  │  =   │
    * ├─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬────┤
    * │       │ (  │ )  │    │    │    │ 0  │ 1  │ 2  │ 3  │    │    │
    * ├────┬──┴─┬──┴─┬──┴─┬──┴────┴──┬─┴────┴──┬─┴───┬┴────┴─┬──┴────┤
    * │    │    │    │    │          │         │     │       │       │
    * └────┴────┴────┴────┴──────────┴─────────┴─────┴───────┴───────┘
    */
    /* 3: Function Layer
    * TODO: Add sound and system keys (screenshots?)
    * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬───────┐
    * │RST │ F1 │ F2 │ F3 │ F4 │ F5 │ F6 │ F7 │ F8 │ F9 │F10 │ F11   │  
    * ├────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬──────┤
    * │     │    │    │    │    │    │    │    │    │    │    │ F12  │
    * ├─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬────┤
    * │       │    │    │    │    │    │    │    │    │    │    │    │
    * ├────┬──┴─┬──┴─┬──┴─┬──┴────┴──┬─┴────┴──┬─┴───┬┴────┴─┬──┴────┤
    * │    │    │    │    │          │         │     │       │       │
    * └────┴────┴────┴────┴──────────┴─────────┴─────┴───────┴───────┘
    */
    /* 4: Macro Layer
    * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬───────┐
    * │    │    │    │    │    │    │    │    │    │    │    │       │  
    * ├────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬──────┤
    * │     │    │    │    │    │    │    │    │    │    │    │      │
    * ├─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬────┤
    * │       │    │    │    │    │    │    │    │    │    │    │    │
    * ├────┬──┴─┬──┴─┬──┴─┬──┴────┴──┬─┴────┴──┬─┴───┬┴────┴─┬──┴────┤
    * │    │    │    │    │          │         │     │       │       │
    * └────┴────┴────┴────┴──────────┴─────────┴─────┴───────┴───────┘
    */
    /* 5: Mouse Layer
    * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬───────┐
    * │    │    │    │    │    │    │SC U│SC L│ UP │SC R│    │       │  
    * ├────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬──────┤
    * │     │    │R CK│M CK│L CK│    │SC D│LEFT│DOWN│RGHT│    │      │
    * ├─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬────┤
    * │       │    │    │    │    │    │    │    │    │    │    │    │
    * ├────┬──┴─┬──┴─┬──┴─┬──┴────┴──┬─┴────┴──┬─┴───┬┴────┴─┬──┴────┤
    * │    │    │    │    │RIGHT CLK │LEFT CLK │     │       │       │
    * └────┴────┴────┴────┴──────────┴─────────┴─────┴───────┴───────┘
    */


    /* 0: Main Layer
    * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬───────┐
    * │ESC │ Q  │ W  │ E  │ R  │ T  │ Y  │ U  │ I  │ O  │ P  │ BACK  │  
    * ├────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬──────┤
    * │↹(MS)│ A  │ S  │ D  │ F  │ G  │ H  │ J  │ K  │ L  │ ;  │ '    │
    * ├─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬────┤
    * │ LSHFT │ Z  │ X  │ C  │ V  │ B  │ N  │ M  │ ,  │ .  │ /  │RSFT│
    * ├────┬──┴─┬──┴─┬──┴─┬──┴────┴──┬─┴────┴──┬─┴───┬┴────┴─┬──┴────┤
    * │LCTL│LALT│(NB)│LCMD│ENTER(SP) │  SPACE  │(NB) │ (MC)  │ (FN)  │
    * └────┴────┴────┴────┴──────────┴─────────┴─────┴───────┴───────┘
    */
    [_MN] = LAYOUT_command(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        MS_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LALT, MO(_NB), KC_LCMD,          SP_ENT,  KC_SPC,                    MO(_NB), MO(_MC), MO(_FN)
    ),

    /* 1: Special Layer
    * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬───────┐
    * │ `  │CAPS│TB L│N TB│TB R│    │PGUP│HOME│ UP │END │    │ DEL   │  
    * ├────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬──────┤
    * │     │    │SP_L│APP │SP_R│    │PGDN│LEFT│DOWN│RGHT│ -  │  =   │
    * ├─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬────┤
    * │       │ (  │ )  │CLOS│    │    │    │    │ [  │ ]  │ \  │    │
    * ├────┬──┴─┬──┴─┬──┴─┬──┴────┴──┬─┴────┴──┬─┴───┬┴────┴─┬──┴────┤
    * │    │    │    │    │          │         │     │       │       │
    * └────┴────┴────┴────┴──────────┴─────────┴─────┴───────┴───────┘
    */
    [_SP] = LAYOUT_command(
        KC_GRV,  KC_CAPS, TB_L   , TB_NEW,  TB_R,    XXXXXXX, KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX, KC_DEL,
        _______, XXXXXXX, M_SPC_L, CMD_TAB, M_SPC_R, XXXXXXX, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_MINS, KC_EQL,
        _______, KC_LPRN, KC_RPRN, TB_CLS,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS, _______,
        _______, _______, _______, _______,          _______, _______,                   _______, _______, _______
    ),

    /* 2: Number Layer
    * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬───────┐
    * │    │ 1  │ 2  │ 3  │ 4  │ 5  │ 6  │ 7  │ 8  │ 9  │ 0  │ BACK  │  
    * ├────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬──────┤
    * │     │ +  │ -  │ *  │ /  │ ^  │    │ 4  │ 5  │ 6  │ -  │  =   │
    * ├─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬────┤
    * │       │ (  │ )  │    │    │    │ 0  │ 1  │ 2  │ 3  │    │    │
    * ├────┬──┴─┬──┴─┬──┴─┬──┴────┴──┬─┴────┴──┬─┴───┬┴────┴─┬──┴────┤
    * │    │    │    │    │          │         │     │       │       │
    * └────┴────┴────┴────┴──────────┴─────────┴─────┴───────┴───────┘
    */
    [_NB] = LAYOUT_command(
        XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        _______, KC_PLUS, KC_MINS, KC_ASTR, KC_SLSH, KC_CIRC, XXXXXXX, KC_4,    KC_5,    KC_6,    KC_MINS, KC_EQL,
        _______, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX, XXXXXXX, KC_0,    KC_1,    KC_2,    KC_3,    XXXXXXX, _______,
        _______, _______, _______, _______,          _______, _______,                   _______, _______, _______
    ),

    /* 3: Function Layer
    * TODO: Add sound and system keys (screenshots?)
    * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬───────┐
    * │RST │ F1 │ F2 │ F3 │ F4 │ F5 │ F6 │ F7 │ F8 │ F9 │F10 │ F11   │  
    * ├────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬──────┤
    * │     │    │    │    │    │    │    │    │    │    │    │ F12  │
    * ├─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬────┤
    * │       │    │    │    │    │    │    │    │    │    │    │    │
    * ├────┬──┴─┬──┴─┬──┴─┬──┴────┴──┬─┴────┴──┬─┴───┬┴────┴─┬──┴────┤
    * │    │    │    │    │          │         │     │       │       │
    * └────┴────┴────┴────┴──────────┴─────────┴─────┴───────┴───────┘
    */
    [_FN] = LAYOUT_command(
        TD_RST,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_F12,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______,          _______, _______,                   _______, _______, _______
    ),

    /* 4: Macro Layer
    * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬───────┐
    * │    │    │    │    │    │    │    │    │    │    │    │       │  
    * ├────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬──────┤
    * │     │    │    │    │    │    │    │    │    │    │    │      │
    * ├─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬────┤
    * │       │    │    │    │    │    │    │    │    │    │    │    │
    * ├────┬──┴─┬──┴─┬──┴─┬──┴────┴──┬─┴────┴──┬─┴───┬┴────┴─┬──┴────┤
    * │    │    │    │    │          │         │     │       │       │
    * └────┴────┴────┴────┴──────────┴─────────┴─────┴───────┴───────┘
    */
    [_MC] = LAYOUT_command(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, _______, _______,          _______, _______,                   _______, _______, _______
    ),

    /* 5: Mouse Layer
    // Note: Scroll down and up are inverted because of MacOS.
    * ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬───────┐
    * │    │    │    │    │    │    │SC D│SC L│ UP │SC R│    │       │  
    * ├────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬──────┤
    * │     │    │R CK│M CK│L CK│    │SC U│LEFT│DOWN│RGHT│    │      │
    * ├─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬────┤
    * │       │    │    │    │    │    │    │    │    │    │    │    │
    * ├────┬──┴─┬──┴─┬──┴─┬──┴────┴──┬─┴────┴──┬─┴───┬┴────┴─┬──┴────┤
    * │    │    │    │    │RIGHT CLK │LEFT CLK │     │       │       │
    * └────┴────┴────┴────┴──────────┴─────────┴─────┴───────┴───────┘
    */
    [_MS] = LAYOUT_command(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_D, KC_WH_L, KC_MS_U, KC_WH_R, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, KC_BTN2, KC_BTN3, KC_BTN1, XXXXXXX, KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______,          KC_BTN2, KC_BTN1,                   _______, _______, _______
    ),
};  

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CMD_TAB:
      if (record->event.pressed) {
        if (!is_cmd_tab_active) {
          is_cmd_tab_active = true;
          register_code(KC_LCMD);
        } 
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_cmd_tab_active) {
    if (IS_LAYER_OFF(_SP)) {
      unregister_code(KC_LCMD);
      is_cmd_tab_active = false;
    }
  }
}

