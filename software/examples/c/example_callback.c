#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_dual_button_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Dual Button Bricklet 2.0

// Callback function for state changed callback
void cb_state_changed(uint8_t button_l, uint8_t button_r, uint8_t led_l, uint8_t led_r,
                      void *user_data) {
	(void)led_l; (void)led_r; (void)user_data; // avoid unused parameter warning

	if(button_l == DUAL_BUTTON_V2_BUTTON_STATE_PRESSED) {
		printf("Left button pressed\n");
	} else {
		printf("Left button released\n");
	}

	if(button_r == DUAL_BUTTON_V2_BUTTON_STATE_PRESSED) {
		printf("Right button pressed\n");
	} else {
		printf("Right button released\n");
	}

	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	DualButtonV2 db;
	dual_button_v2_create(&db, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register state changed callback to function cb_state_changed
	dual_button_v2_register_callback(&db,
	                                 DUAL_BUTTON_V2_CALLBACK_STATE_CHANGED,
	                                 (void *)cb_state_changed,
	                                 NULL);

	printf("Press key to exit\n");
	getchar();
	dual_button_v2_destroy(&db);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
