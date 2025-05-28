#include QMK_KEYBOARD_H

enum layers {
	BASE_LAYER = 0,
	ARROW_KEYS_LAYER,
	FUNCTION_LAYER,
	MEDIA_KEYS_LAYER
};

enum custom_keycodes {
	FN_ESC = SAFE_RANGE,
	TG_AKL,
	MO_MKL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE_LAYER] = LAYOUT_60_ansi(
		QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		FN_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
		KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                                      XXXXXXX, KC_RGUI, KC_RALT, KC_RCTL
	),

	[ARROW_KEYS_LAYER] = LAYOUT_60_ansi(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_UP,
		_______, _______, _______,                   _______,                                     XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT
	),

	[FUNCTION_LAYER] = LAYOUT_60_ansi(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
		_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_HOME, KC_END,  KC_INS,
		_______, TG_AKL,  C(KC_S), MO_MKL,  XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, KC_PGUP,          _______,
		_______,          XXXXXXX, XXXXXXX, KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, KC_APP,  KC_SCRL, KC_PAUS, KC_PGDN,          _______,
		_______, _______, _______,                   _______,                                     XXXXXXX, _______, _______, _______
	),

	[MEDIA_KEYS_LAYER] = LAYOUT_60_ansi(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_MPRV, KC_MNXT, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
		_______, _______, _______,                   _______,                                     XXXXXXX, _______, _______, _______
	)
};

bool
process_record_user(uint16_t keycode, keyrecord_t *record)
{
	enum process_record_user_constants {
		FN_KEY_TAP_TIMEOUT = 500
	};

	static uint16_t fn_key_tap_time = 0;
	static bool fn_key_is_tapped = false;

	switch (keycode) {
	case FN_ESC:
		if (record->event.pressed) {
			fn_key_is_tapped = true;
			fn_key_tap_time = record->event.time;
			layer_on(FUNCTION_LAYER);
		} else {
			layer_off(FUNCTION_LAYER);

			if (fn_key_is_tapped &&
			    timer_elapsed(fn_key_tap_time) < FN_KEY_TAP_TIMEOUT) {
				tap_code(KC_ESC);
			}

			fn_key_is_tapped = false;
		}

		return false;
	case TG_AKL:
		if (record->event.pressed) {
			layer_invert(ARROW_KEYS_LAYER);
		}

		fn_key_is_tapped = false;
		return false;
	case MO_MKL:
		if (record->event.pressed) {
			layer_on(MEDIA_KEYS_LAYER);
		} else {
			layer_off(MEDIA_KEYS_LAYER);
		}

		fn_key_is_tapped = false;
		return false;
	default:
		fn_key_is_tapped = false;
		return true;
	}
}
