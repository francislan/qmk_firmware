#include QMK_KEYBOARD_H

#define MS_TAB  LT(_MS, KC_TAB)

// Browser tabs manipulation (MacOS)
#define TB_CLS  LCMD(KC_W)
#define TB_NEW  LCMD(KC_T)
#define TB_R    LCTL(KC_TAB)
#define TB_L    LCTL(LSFT(KC_TAB))

// MacOS specific space moving.
#define M_SPC_L LCTL(KC_LEFT)
#define M_SPC_R LCTL(KC_RGHT)

// MacOS Home and End (Modify iTerm Key: LCMD + LEFT -> Hex Code 001 and LCMD + RIGHT -> Hex Code 005)
#define MAC_HOME LCMD(KC_LEFT)
#define MAC_END  LCMD(KC_RGHT)

// Tap dance
#define TD_RST TD(TD_RESET)

// Super CMD + TAB: Keeps CMD pressed until the special layer is deactivated.
bool is_cmd_tab_active = false;

enum custom_keycodes {
  CMD_TAB = SAFE_RANGE,  // "Super" CMD+TAB.
  // Macros
  VIM_QT,    // Exit Vim
  VIM_CT,    // Close top tab in Vim
  VIM_CP,    // Copy to Clipboard in Vim
  VIM_PST,   // Paste from Clipboard in Vim
  BZ_TEST,   // Blaze test
};

// Tap dance
enum {
  TD_RESET = 0  // Put into DFU mode after 5 presses.
};

void td_reset(qk_tap_dance_state_t *state, void *user_data) {
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
  _MS,  // Mouse
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 0: Main Layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┐           ┌─────┬─────┬─────┬─────┬─────┬─────┐
   * │ ESC │  Q  │  W  │  E  │  R  │  T  │           │  Y  │  U  │  I  │  O  │  P  │BACK │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │↹(MS)│  A  │  S  │  D  │  F  │  G  │           │  H  │  J  │  K  │  L  │  ;  │ENTER│
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │LSHFT│  Z  │  X  │  C  │  V  │  B  │           │  N  │  M  │  ,  │  .  │  /  │LALT │
   * └─────┴─────┴─────┴──┬──┴──┬──┴──┬──┴──┐     ┌──┴──┬──┴──┬──┴──┬──┴─────┴─────┴─────┘
   *                      │LCTRL│LCMD │(SP) │     │SPACE│(NB) │(FN) │
   *                      └─────┴─────┴─────┘     └─────┴─────┴─────┘
   */
  /* 1: Special Layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┐           ┌─────┬─────┬─────┬─────┬─────┬─────┐
   * │  `  │CAPS │TAB L│N TAB│TAB R│     │           │PG UP│HOME │ UP  │ END │  =  │ DEL │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │SP L │ APP │SP R │     │           │PG DN│LEFT │DOWN │RIGHT│  -  │  '  │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │  (  │  )  │C TAB│     │     │           │     │     │  [  │  ]  │  \  │     │
   * └─────┴─────┴─────┴──┬──┴──┬──┴──┬──┴──┐     ┌──┴──┬──┴──┬──┴──┬──┴─────┴─────┴─────┘
   *                      │     │     │     │     │     │     │     │
   *                      └─────┴─────┴─────┘     └─────┴─────┴─────┘
   */
  /* 2: Number Layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┐           ┌─────┬─────┬─────┬─────┬─────┬─────┐
   * │     │  1  │  2  │  3  │  4  │  5  │           │  6  │  7  │  8  │  9  │  0  │BACK │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │  +  │  -  │  *  │  /  │  ^  │           │     │  4  │  5  │  6  │  -  │  =  │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │  (  │  )  │     │     │     │           │  0  │  1  │  2  │  3  │     │     │
   * └─────┴─────┴─────┴──┬──┴──┬──┴──┬──┴──┐     ┌──┴──┬──┴──┬──┴──┬──┴─────┴─────┴─────┘
   *                      │     │     │     │     │     │     │     │
   *                      └─────┴─────┴─────┘     └─────┴─────┴─────┘
   */
  /* 3: Function Layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┐           ┌─────┬─────┬─────┬─────┬─────┬─────┐
   * │RESET│VMQT │     │     │     │BZTS │           │     │ F7  │ F8  │ F9  │ F10 │ F11 │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │VMCT │     │     │     │     │           │     │ F4  │ F5  │ F6  │     │ F12 │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │VMCP │CMPT │     │           │     │ F1  │ F2  │ F3  │     │     │
   * └─────┴─────┴─────┴──┬──┴──┬──┴──┬──┴──┐     ┌──┴──┬──┴──┬──┴──┬──┴─────┴─────┴─────┘
   *                      │     │     │     │     │     │     │     │
   *                      └─────┴─────┴─────┘     └─────┴─────┴─────┘
   */
  /* 4: Mouse Layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┐           ┌─────┬─────┬─────┬─────┬─────┬─────┐
   * │     │     │     │     │     │     │           │SC UP│SC L │ UP  │SC R │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │R CLK│M CLK│L CLK│     │           │SC DN│LEFT │DOWN │RIGHT│     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │     │           │     │     │     │     │     │     │
   * └─────┴─────┴─────┴──┬──┴──┬──┴──┬──┴──┐     ┌──┴──┬──┴──┬──┴──┬──┴─────┴─────┴─────┘
   *                      │     │     │R CLK│     │L CLK│     │     │
   *                      └─────┴─────┴─────┘     └─────┴─────┴─────┘
   */

  /* 0: Main Layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┐           ┌─────┬─────┬─────┬─────┬─────┬─────┐
   * │ ESC │  Q  │  W  │  E  │  R  │  T  │           │  Y  │  U  │  I  │  O  │  P  │BACK │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │↹(MS)│  A  │  S  │  D  │  F  │  G  │           │  H  │  J  │  K  │  L  │  ;  │ENTER│
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │LSHFT│  Z  │  X  │  C  │  V  │  B  │           │  N  │  M  │  ,  │  .  │  /  │LALT │
   * └─────┴─────┴─────┴──┬──┴──┬──┴──┬──┴──┐     ┌──┴──┬──┴──┬──┴──┬──┴─────┴─────┴─────┘
   *                      │LCTRL│LCMD │(SP) │     │SPACE│(NB) │(FN) │
   *                      └─────┴─────┴─────┘     └─────┴─────┴─────┘
   */
  [_MN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       MS_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_LALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, KC_LCMD, MO(_SP),     KC_SPC, MO(_NB), MO(_FN)
                                      //`--------------------------'  `--------------------------'
  ),

  /* 1: Special Layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┐           ┌─────┬─────┬─────┬─────┬─────┬─────┐
   * │  `  │CAPS │TAB L│N TAB│TAB R│     │           │PG UP│HOME │ UP  │ END │  =  │ DEL │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │SP L │ APP │SP R │     │           │PG DN│LEFT │DOWN │RIGHT│  -  │  '  │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │  (  │  )  │C TAB│     │     │           │     │     │  [  │  ]  │  \  │     │
   * └─────┴─────┴─────┴──┬──┴──┬──┴──┬──┴──┐     ┌──┴──┬──┴──┬──┴──┬──┴─────┴─────┴─────┘
   *                      │     │     │     │     │     │     │     │
   *                      └─────┴─────┴─────┘     └─────┴─────┴─────┘
   */
  [_SP] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV, KC_CAPS,    TB_L,  TB_NEW,    TB_R, XXXXXXX,                      KC_PGUP,MAC_HOME,   KC_UP, MAC_END,  KC_EQL,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, M_SPC_L, CMD_TAB, M_SPC_R, XXXXXXX,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_MINS, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LPRN, KC_RPRN,  TB_CLS, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  /* 2: Number Layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┐           ┌─────┬─────┬─────┬─────┬─────┬─────┐
   * │     │  1  │  2  │  3  │  4  │  5  │           │  6  │  7  │  8  │  9  │  0  │BACK │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │  +  │  -  │  *  │  /  │  ^  │           │     │  4  │  5  │  6  │  -  │  =  │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │  (  │  )  │     │     │     │           │  0  │  1  │  2  │  3  │     │     │
   * └─────┴─────┴─────┴──┬──┴──┬──┴──┬──┴──┐     ┌──┴──┬──┴──┬──┴──┬──┴─────┴─────┴─────┘
   *                      │     │     │     │     │     │     │     │
   *                      └─────┴─────┴─────┘     └─────┴─────┴─────┘
   */
  [_NB] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_PLUS, KC_MINS, KC_ASTR, KC_SLSH, KC_CIRC,                      XXXXXXX,    KC_4,    KC_5,    KC_6, KC_MINS,  KC_EQL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX, XXXXXXX,                         KC_0,    KC_1,    KC_2,    KC_3, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  /* 3: Function Layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┐           ┌─────┬─────┬─────┬─────┬─────┬─────┐
   * │RESET│VMQT │     │     │     │BZTS │           │     │ F7  │ F8  │ F9  │ F10 │ F11 │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │VMCT │     │     │     │     │           │     │ F4  │ F5  │ F6  │     │ F12 │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │VMCP │CMPT │     │           │     │ F1  │ F2  │ F3  │     │     │
   * └─────┴─────┴─────┴──┬──┴──┬──┴──┬──┴──┐     ┌──┴──┬──┴──┬──┴──┬──┴─────┴─────┴─────┘
   *                      │     │     │     │     │     │     │     │
   *                      └─────┴─────┴─────┘     └─────┴─────┴─────┘
   */
  [_FN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       TD_RST,  VIM_QT, XXXXXXX, XXXXXXX, XXXXXXX, BZ_TEST,                      XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  VIM_CT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,   KC_F4,   KC_F5,   KC_F6, XXXXXXX,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX,  VIM_CP, VIM_PST, XXXXXXX,                      XXXXXXX,   KC_F1,   KC_F2,   KC_F3, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  /* 4: Mouse Layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┐           ┌─────┬─────┬─────┬─────┬─────┬─────┐
   * │     │     │     │     │     │     │           │SC UP│SC L │ UP  │SC R │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │R CLK│M CLK│L CLK│     │           │SC DN│LEFT │DOWN │RIGHT│     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤           ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │     │           │     │     │     │     │     │     │
   * └─────┴─────┴─────┴──┬──┴──┬──┴──┬──┴──┐     ┌──┴──┬──┴──┬──┴──┬──┴─────┴─────┴─────┘
   *                      │     │     │R CLK│     │L CLK│     │     │
   *                      └─────┴─────┴─────┘     └─────┴─────┴─────┘
   */
  [_MS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_WH_D, KC_WH_L, KC_MS_U, KC_WH_R, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, KC_BTN2, KC_BTN3, KC_BTN1, XXXXXXX,                      KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_master) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_name(void) {
    oled_write_ln_P(PSTR("Francis LAN"), false);
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case _MN:
            oled_write_ln_P(PSTR("Main"), false);
            break;
        case 1 << _SP:
            oled_write_ln_P(PSTR("Special"), false);
            break;
        case 1 << _NB:
            oled_write_ln_P(PSTR("Number"), false);
            break;
        case 1 << _FN:
            oled_write_ln_P(PSTR("Function"), false);
            break;
        case 1 << _MS:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
    }
}

void oled_render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR("Caps Lock: "), false);
    if (led_usb_state & (1 << USB_LED_CAPS_LOCK)) {
        oled_write_ln_P(PSTR("Y"), true);
    } else {
        oled_write_ln_P(PSTR("N"), false);
    }
}

void oled_render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Ctrl"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Shift"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Alt"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(PSTR("Cmd"), (modifiers & MOD_MASK_GUI));
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
    if (is_master) {
        oled_render_name();
        oled_render_layer_state();
        oled_render_keylock_status(host_keyboard_leds());
        oled_render_mod_status(get_mods());
    } else {
        oled_render_logo();
    }
}

// Super CMD+TAB
void matrix_scan_user(void) {
  if (is_cmd_tab_active && IS_LAYER_OFF(_SP)) {
    unregister_code(KC_LCMD);
    is_cmd_tab_active = false;
  }
}

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
    case VIM_QT:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESCAPE) SS_TAP(X_ESCAPE) ":wq" SS_TAP(X_ENTER));
      }
      break;
    case VIM_CT:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESCAPE) SS_TAP(X_ESCAPE) SS_LCTRL("wk") ":q" SS_TAP(X_ENTER));
      }
      break;
    case VIM_CP:
      if (record->event.pressed) {
        SEND_STRING("\"*y");
      }
      break;
    case VIM_PST:
      if (record->event.pressed) {
        SEND_STRING("\"*p");
      }
      break;
    case BZ_TEST:
      if (record->event.pressed) {
        SEND_STRING("blaze test : --test_output=all --strip=never --nocache_test_results --runs_per_test=1");
        SEND_STRING(SS_TAP(X_HOME) SS_DOWN(X_LALT) SS_TAP(X_RIGHT) SS_TAP(X_RIGHT) SS_TAP(X_RIGHT) SS_UP(X_LALT) SS_TAP(X_RIGHT));
      }
      break;
    }
  return true;
}
