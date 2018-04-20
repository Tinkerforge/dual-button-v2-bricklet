/* dual-button-v2-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config_button.h: Logging configuration for Dual Button V2 Bricklet
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef CONFIG_BUTTON_H
#define CONFIG_BUTTOH_H

#include "xmc_gpio.h"

#define BUTTON_LED_L_PIN     P2_1
#define BUTTON_LED_R_PIN     P0_9

#define BUTTON_SWITCH_L_PIN  P2_2
#define BUTTON_SWITCH_R_PIN  P0_8

#endif