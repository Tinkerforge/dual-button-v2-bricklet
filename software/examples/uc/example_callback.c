#include "bindings/hal_common.h"
#include "bindings/bricklet_dual_button_v2.h"

#define UID "XYZ" // Change XYZ to the UID of your Dual Button Bricklet 2.0

void check(int rc, const char* msg);

void example_setup(TF_HalContext *hal);
void example_loop(TF_HalContext *hal);


// Callback function for state changed callback
static void state_changed_handler(TF_DualButtonV2 *device, uint8_t button_l,
                                  uint8_t button_r, uint8_t led_l, uint8_t led_r,
                                  void *user_data) {
	(void)device; (void)led_l; (void)led_r; (void)user_data; // avoid unused parameter warning

	if(button_l == TF_DUAL_BUTTON_V2_BUTTON_STATE_PRESSED) {
		tf_hal_printf("Left Button: Pressed\n");
	} else if(button_l == TF_DUAL_BUTTON_V2_BUTTON_STATE_RELEASED) {
		tf_hal_printf("Left Button: Released\n");
	}

	if(button_r == TF_DUAL_BUTTON_V2_BUTTON_STATE_PRESSED) {
		tf_hal_printf("Right Button: Pressed\n");
	} else if(button_r == TF_DUAL_BUTTON_V2_BUTTON_STATE_RELEASED) {
		tf_hal_printf("Right Button: Released\n");
	}

	tf_hal_printf("\n");
}

static TF_DualButtonV2 db;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_dual_button_v2_create(&db, UID, hal), "create device object");

	// Register state changed callback to function state_changed_handler
	tf_dual_button_v2_register_state_changed_callback(&db,
	                                                  state_changed_handler,
	                                                  NULL);

	// Enable state changed callback
	check(tf_dual_button_v2_set_state_changed_callback_configuration(&db,
	                                                                 true), "call set_state_changed_callback_configuration");
}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
