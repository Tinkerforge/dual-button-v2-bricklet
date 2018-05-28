<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletDualButtonV2.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletDualButtonV2;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Dual Button Bricklet 2.0

// Callback function for state changed callback
function cb_stateChanged($button_l, $button_r, $led_l, $led_r)
{
    if ($button_l == BrickletDualButtonV2::BUTTON_STATE_PRESSED) {
        echo "Left Button: Pressed\n";
    } elseif ($button_l == BrickletDualButtonV2::BUTTON_STATE_RELEASED) {
        echo "Left Button: Released\n";
    }

    if ($button_r == BrickletDualButtonV2::BUTTON_STATE_PRESSED) {
        echo "Right Button: Pressed\n";
    } elseif ($button_r == BrickletDualButtonV2::BUTTON_STATE_RELEASED) {
        echo "Right Button: Released\n";
    }

    echo "\n";
}

$ipcon = new IPConnection(); // Create IP connection
$db = new BrickletDualButtonV2(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Register state changed callback to function cb_stateChanged
$db->registerCallback(BrickletDualButtonV2::CALLBACK_STATE_CHANGED, 'cb_stateChanged');

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
