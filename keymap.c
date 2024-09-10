#include QMK_KEYBOARD_H

enum layer_names {
	_BASE_LAYER,
	_ARROW_KEYS_LAYER,
	_FUNCTION_LAYER
};

enum custom_keycodes {
	FN_ESC = SAFE_RANGE,
	TG_AKL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE_LAYER] = LAYOUT_60_ansi(
		QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		FN_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
		KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                                      XXXXXXX, KC_RGUI, KC_RALT, KC_RCTL
	),

	[_ARROW_KEYS_LAYER] = LAYOUT_60_ansi(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_UP,
		_______, _______, _______,                   _______,                                     XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT
	),

	[_FUNCTION_LAYER] = LAYOUT_60_ansi(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
		KC_CAPS, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_HOME, KC_END,  KC_INS,
		_______, TG_AKL,  C(KC_S), XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, KC_PGUP,          _______,
		_______,          KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, KC_APP,  KC_SCRL, KC_PAUS, KC_PGDN,          _______,
		_______, _______, _______,                   _______,                                     XXXXXXX, _______, _______, _______
	)
};

bool
process_record_user(uint16_t keycode, keyrecord_t *record)
{
	static const uint16_t fn_tap_timeout = 500;
	static bool fn_tap = false;
	static uint16_t fn_tap_time = 0;

	switch (keycode) {
	case FN_ESC:
		if (record->event.pressed) {
			fn_tap = true;
			fn_tap_time = record->event.time;
			layer_on(_FUNCTION_LAYER);
		} else {
			layer_off(_FUNCTION_LAYER);

			if (fn_tap
			    && timer_elapsed(fn_tap_time) < fn_tap_timeout) {
				tap_code(KC_ESC);
			}

			fn_tap = false;
		}

		return false;
	case TG_AKL:
		if (record->event.pressed) {
			layer_invert(_ARROW_KEYS_LAYER);
		}

		fn_tap = false;
		return false;
	default:
		fn_tap = false;
		return true;
	}
}
