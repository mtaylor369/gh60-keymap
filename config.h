#ifndef CONFIG_USER_H
#define CONFIG_USER_H

/* Set up USB device descriptor parameters. */
#undef MANUFACTURER
#define MANUFACTURER "QMK Firmware"
#undef PRODUCT
#define PRODUCT "GH60 RevCHN"

/* Set up grave escape overrides. */
#ifndef GRAVE_ESC_ALT_OVERRIDE
#define GRAVE_ESC_ALT_OVERRIDE
#endif /* GRAVE_ESC_ALT_OVERRIDE */
#ifndef GRAVE_ESC_CTRL_OVERRIDE
#define GRAVE_ESC_CTRL_OVERRIDE
#endif /* GRAVE_ESC_CTRL_OVERRIDE */
#ifndef GRAVE_ESC_GUI_OVERRIDE
#define GRAVE_ESC_GUI_OVERRIDE
#endif /* GRAVE_ESC_GUI_OVERRIDE */
#undef GRAVE_ESC_SHIFT_OVERRIDE

/* Disable mechanical locking support. */
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

/* Disable unnecessary debugging and action features. */
#ifndef NO_DEBUG
#define NO_DEBUG
#endif /* NO_DEBUG */
#ifndef NO_PRINT
#define NO_PRINT
#endif /* NO_PRINT */
#ifndef NO_ACTION_TAPPING
#define NO_ACTION_TAPPING
#endif /* NO_ACTION_TAPPING */
#ifndef NO_ACTION_ONESHOT
#define NO_ACTION_ONESHOT
#endif /* NO_ACTION_ONESHOT */

#endif /* CONFIG_USER_H */
