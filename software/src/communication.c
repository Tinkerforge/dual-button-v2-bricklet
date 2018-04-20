/* dual-button-v2-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.c: TFP protocol message handling
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

#include "communication.h"

#include "bricklib2/utility/communication_callback.h"
#include "bricklib2/protocols/tfp/tfp.h"

#include "configs/config_button.h"
#include "button.h"
#include "xmc_gpio.h"

BootloaderHandleMessageResponse handle_message(const void *message, void *response) {
	switch(tfp_get_fid_from_message(message)) {
		case FID_SET_LED_STATE: return set_led_state(message);
		case FID_GET_LED_STATE: return get_led_state(message, response);
		case FID_GET_BUTTON_STATE: return get_button_state(message, response);
		case FID_SET_SELECTED_LED_STATE: return set_selected_led_state(message);
		case FID_SET_STATE_CHANGED_CALLBACK_CONFIGURATION: return set_state_changed_callback_configuration(message);
		case FID_GET_STATE_CHANGED_CALLBACK_CONFIGURATION: return get_state_changed_callback_configuration(message, response);
		default: return HANDLE_MESSAGE_RESPONSE_NOT_SUPPORTED;
	}
}



BootloaderHandleMessageResponse set_led_state(const SetLEDState *data) {
	if(data->led_r < DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_ON || data->led_r > DUAL_BUTTON_V2_LED_STATE_OFF ||
	   data->led_l < DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_ON || data->led_l > DUAL_BUTTON_V2_LED_STATE_OFF) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	button.led_l = data->led_l;
	button.led_r = data->led_r;

	if(data->led_l == DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_ON || data->led_l == DUAL_BUTTON_V2_LED_STATE_ON) {
		XMC_GPIO_SetOutputLow(BUTTON_LED_L_PIN);
	} else {
		XMC_GPIO_SetOutputHigh(BUTTON_LED_L_PIN);
	}

	if(data->led_r == DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_ON || data->led_r == DUAL_BUTTON_V2_LED_STATE_ON) {
		XMC_GPIO_SetOutputLow(BUTTON_LED_R_PIN);
	} else {
		XMC_GPIO_SetOutputHigh(BUTTON_LED_R_PIN);
	}

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_led_state(const GetLEDState *data, GetLEDState_Response *response) {
	response->header.length = sizeof(GetLEDState_Response);
	response->led_l         = button.led_l;
	response->led_r         = button.led_r;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse get_button_state(const GetButtonState *data, GetButtonState_Response *response) {
	response->header.length = sizeof(GetButtonState_Response);
	response->button_l      = button.button_l;
	response->button_r      = button.button_r;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse set_selected_led_state(const SetSelectedLEDState *data) {
	if(data->state < DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_ON || data->state > DUAL_BUTTON_V2_LED_STATE_OFF ||
	   data->led < DUAL_BUTTON_V2_LED_LEFT || data->led > DUAL_BUTTON_V2_LED_RIGHT) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}
	if(data->led == DUAL_BUTTON_V2_LED_LEFT) {
		button.led_l = data->state;
		if(data->state == DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_ON || data->state == DUAL_BUTTON_V2_LED_STATE_ON) {
			XMC_GPIO_SetOutputLow(BUTTON_LED_L_PIN);
		} else {
			XMC_GPIO_SetOutputHigh(BUTTON_LED_L_PIN);
		}
	}
	
	if(data->led == DUAL_BUTTON_V2_LED_RIGHT) {
		button.led_r = data->state;
		if(data->state == DUAL_BUTTON_V2_LED_STATE_AUTO_TOGGLE_ON || data->state == DUAL_BUTTON_V2_LED_STATE_ON) {
			XMC_GPIO_SetOutputLow(BUTTON_LED_R_PIN);
		} else {
			XMC_GPIO_SetOutputHigh(BUTTON_LED_R_PIN);
		}
	}

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse set_state_changed_callback_configuration(const SetStateChangedCallbackConfiguration *data) {
	button.state_changed_callback_enabled = data->enabled;

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_state_changed_callback_configuration(const GetStateChangedCallbackConfiguration *data, GetStateChangedCallbackConfiguration_Response *response) {
	response->header.length = sizeof(GetStateChangedCallbackConfiguration_Response);
	response->enabled       = button.state_changed_callback_enabled;
	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}




bool handle_state_changed_callback(void) {
	static bool is_buffered = false;
	static StateChanged_Callback cb;

	if(!is_buffered && button.state_changed_callback_enabled && button.state_changed) {
		button.state_changed = false;
		tfp_make_default_header(&cb.header, bootloader_get_uid(), sizeof(StateChanged_Callback), FID_CALLBACK_STATE_CHANGED);

		cb.button_l = button.button_l;
		cb.button_r	= button.button_r;
		cb.led_l    = button.led_l;
		cb.led_r    = button.led_r;
	} else {
		return false;
	}

	if(bootloader_spitfp_is_send_possible(&bootloader_status.st)) {
		bootloader_spitfp_send_ack_and_message(&bootloader_status, (uint8_t*)&cb, sizeof(StateChanged_Callback));
		is_buffered = false;
		return true;
	} else {
		is_buffered = true;
	}

	return false;
}

void communication_tick(void) {
	communication_callback_tick();
}

void communication_init(void) {
	communication_callback_init();
}
