var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change XYZ to the UID of your Dual Button Bricklet 2.0

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var db = new Tinkerforge.BrickletDualButtonV2(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

// Register state changed callback
db.on(Tinkerforge.BrickletDualButtonV2.CALLBACK_STATE_CHANGED,
    // Callback function for state changed callback
    function (buttonL, buttonR, ledL, ledR) {
        if(buttonL === Tinkerforge.BrickletDualButtonV2.BUTTON_STATE_PRESSED) {
            console.log('Left Button: Pressed');
        }
        else if(buttonL === Tinkerforge.BrickletDualButtonV2.BUTTON_STATE_RELEASED) {
            console.log('Left Button: Released');
        }

        if(buttonR === Tinkerforge.BrickletDualButtonV2.BUTTON_STATE_PRESSED) {
            console.log('Right Button: Pressed');
        }
        else if(buttonR === Tinkerforge.BrickletDualButtonV2.BUTTON_STATE_RELEASED) {
            console.log('Right Button: Released');
        }

        console.log();
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
