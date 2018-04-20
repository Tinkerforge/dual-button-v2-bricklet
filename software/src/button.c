/* dual-button-v2-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * button.c: Button/LED driver
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

#include "button.h"

#include "bricklib2/hal/system_timer/system_timer.h"

#include "communication.h"
#include "configs/config_button.h"

#include "xmc_gpio.h"

#define BUTTON_L 0
#define BUTTON_R 1

Button button;

void button_next_led_toggle_state(const uint8_t b) {
	switch(b) {
		case BUTTON_R: {
			if(button.led_r == DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_OFF) {
				XMC_GPIO_SetOutputLow(BUTTON_LED_R_PIN);
				button.led_r = DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_ON;
			} else if(button.led_r == DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_ON) {
				XMC_GPIO_SetOutputHigh(BUTTON_LED_R_PIN);
				button.led_r = DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_OFF;
			}
			break;
		}

		case BUTTON_L: {
			if(button.led_l == DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_OFF) {
				XMC_GPIO_SetOutputLow(BUTTON_LED_L_PIN);
				button.led_l = DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_ON;
			} else if(button.led_l == DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_ON) {
				XMC_GPIO_SetOutputHigh(BUTTON_LED_L_PIN);
				button.led_l = DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_OFF;
			}
			break;
		}
	}
}



void button_init(void) {
    memset(&button, 0, sizeof(Button));

	button.button_r = DUAL_BUTTON_V2_BUTTON_STATE_RELEASED;
	button.button_l = DUAL_BUTTON_V2_BUTTON_STATE_RELEASED;
	button.led_r    = DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_OFF;
	button.led_l    = DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_OFF;

	const XMC_GPIO_CONFIG_t input_pin_config = {
		.mode             = XMC_GPIO_MODE_INPUT_PULL_UP,
		.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
	};

	XMC_GPIO_Init(BUTTON_SWITCH_L_PIN, &input_pin_config);
	XMC_GPIO_Init(BUTTON_SWITCH_R_PIN, &input_pin_config);


	const XMC_GPIO_CONFIG_t output_pin_config = {
		.mode             = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH
	};

	XMC_GPIO_Init(BUTTON_LED_L_PIN, &output_pin_config);
	XMC_GPIO_Init(BUTTON_LED_R_PIN, &output_pin_config);
}

void button_tick(void) {
    if(system_timer_is_time_elapsed_ms(button.button_l_debounce, BUTTON_DEBOUNCE_TIME)) {
		if(XMC_GPIO_GetInput(BUTTON_SWITCH_L_PIN)) {
			if(button.button_l != DUAL_BUTTON_V2_BUTTON_STATE_RELEASED) {
				button.button_l = DUAL_BUTTON_V2_BUTTON_STATE_RELEASED;
				button.button_l_debounce = system_timer_get_ms();
				button.state_changed = true;
			}
		} else {
			if(button.button_l != DUAL_BUTTON_V2_BUTTON_STATE_PRESSED) {
				button_next_led_toggle_state(BUTTON_L);
				button.button_l = DUAL_BUTTON_V2_BUTTON_STATE_PRESSED;
				button.button_l_debounce = system_timer_get_ms();
				button.state_changed = true;
			}
		}
	}

	if(system_timer_is_time_elapsed_ms(button.button_r_debounce, BUTTON_DEBOUNCE_TIME)) {
		if(XMC_GPIO_GetInput(BUTTON_SWITCH_R_PIN)) {
			if(button.button_r != DUAL_BUTTON_V2_BUTTON_STATE_RELEASED) {
				button.button_r = DUAL_BUTTON_V2_BUTTON_STATE_RELEASED;
				button.button_r_debounce = system_timer_get_ms();
				button.state_changed = true;
			}
		} else {
			if(button.button_r != DUAL_BUTTON_V2_BUTTON_STATE_PRESSED) {
				button_next_led_toggle_state(BUTTON_R);
				button.button_r = DUAL_BUTTON_V2_BUTTON_STATE_PRESSED;
				button.button_r_debounce = system_timer_get_ms();
				button.state_changed = true;
			}
		}
	}
}