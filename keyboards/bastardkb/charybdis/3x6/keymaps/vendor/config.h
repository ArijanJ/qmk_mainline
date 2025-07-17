/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#ifdef VIA_ENABLE
/* VIA configuration. */
#    define DYNAMIC_KEYMAP_LAYER_COUNT 12
#endif // VIA_ENABLE

#ifndef __arm__
/* Disable unused features. */
#    define NO_ACTION_ONESHOT
#endif // __arm__

#define TAPPING_TERM 150

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define QUICK_TAP_TERM 0

#define COMBO_TERM 20

#define FORCE_NKRO

/* Charybdis-specific features. */

#define EECONFIG_USER_DATA_SIZE 20

#ifdef POINTING_DEVICE_ENABLE
#undef CHARYBDIS_AUTO_SNIPING_ON_LAYER

// Automatically enable the pointer layer when moving the trackball.  See also:
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS`
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD`

#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 1

#define WHEEL_EXTENDED_REPORT
#define MOUSE_EXTENDED_REPORT
#define POINTING_DEVICE_HIRES_SCROLL_ENABLE
#define POINTING_DEVICE_HIRES_SCROLL_MULTIPLIER 12
#define POINTING_DEVICE_HIRES_SCROLL_EXPONENT 10
#define CHARYBDIS_DRAGSCROLL_BUFFER_SIZE 5
//#define POINTING_DEVICE_TASK_THROTTLE_MS 4

#define CHARYBDIS_MINIMUM_DEFAULT_DPI 225
#define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 75

#define CHARYBDIS_MINIMUM_SNIPING_DPI 150
#define CHARYBDIS_SNIPING_DPI_CONFIG_STEP 50

#define MACCEL_DEBUG
/*
 * Requires enabling float support for printf!
 */
#undef PRINTF_SUPPORT_DECIMAL_SPECIFIERS
#define PRINTF_SUPPORT_DECIMAL_SPECIFIERS 1

// DEFAULTS
// #define MACCEL_TAKEOFF 2.0      // lower/higher value = curve takes off more smoothly/abruptly
// #define MACCEL_GROWTH_RATE 0.25 // lower/higher value = curve reaches its upper limit slower/faster
// #define MACCEL_OFFSET 2.2       // lower/higher value = acceleration kicks in earlier/later
// #define MACCEL_LIMIT 0.2        // lower limit of accel curve (minimum acceleration factor)

#define MACCEL_TAKEOFF 2.7      // lower/higher value = curve takes off more smoothly/abruptly
#define MACCEL_GROWTH_RATE 0.1 // lower/higher value = curve reaches its upper limit slower/faster
#define MACCEL_OFFSET 2.5       // lower/higher value = acceleration kicks in earlier/later
#define MACCEL_LIMIT 0.3       // lower limit of accel curve (minimum acceleration factor)


#endif // POINTING_DEVICE_ENABLE
