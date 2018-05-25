import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletDualButtonV2;

public class ExampleCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your Dual Button Bricklet 2.0
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletDualButtonV2 db = new BrickletDualButtonV2(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Add state changed listener
		db.addStateChangedListener(new BrickletDualButtonV2.StateChangedListener() {
			public void stateChanged(int buttonL, int buttonR, int ledL, int ledR) {
				if(buttonL == BrickletDualButtonV2.BUTTON_STATE_PRESSED) {
					System.out.println("Left button pressed");
				} else {
					System.out.println("Left button released");
				}

				if(buttonR == BrickletDualButtonV2.BUTTON_STATE_PRESSED) {
					System.out.println("Right button pressed");
				} else {
					System.out.println("Right button released");
				}

				System.out.println("");
			}
		});

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
