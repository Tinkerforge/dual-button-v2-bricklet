package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/dual_button_v2_bricklet"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your Dual Button Bricklet 2.0.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	db, _ := dual_button_v2_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	db.RegisterStateChangedCallback(func(buttonL dual_button_v2_bricklet.ButtonState, buttonR dual_button_v2_bricklet.ButtonState, ledL dual_button_v2_bricklet.LEDState, ledR dual_button_v2_bricklet.LEDState) {

		if buttonL == dual_button_v2_bricklet.ButtonStatePressed {
			fmt.Println("Left Button: Pressed")
		} else if buttonL == dual_button_v2_bricklet.ButtonStateReleased {
			fmt.Println("Left Button: Released")
		}

		if buttonR == dual_button_v2_bricklet.ButtonStatePressed {
			fmt.Println("Right Button: Pressed")
		} else if buttonR == dual_button_v2_bricklet.ButtonStateReleased {
			fmt.Println("Right Button: Released")
		}

		fmt.Println()
	})

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
