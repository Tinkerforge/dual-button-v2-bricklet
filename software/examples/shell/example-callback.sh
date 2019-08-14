#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Dual Button Bricklet 2.0

# Handle incoming state changed callbacks
tinkerforge dispatch dual-button-v2-bricklet $uid state-changed &

# Enable state changed callback
tinkerforge call dual-button-v2-bricklet $uid set-state-changed-callback-configuration true

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
