function octave_example_callback()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Dual Button Bricklet 2.0

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    db = javaObject("com.tinkerforge.BrickletDualButtonV2", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register state changed callback to function cb_state_changed
    db.addStateChangedCallback(@cb_state_changed);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for state changed callback
function cb_state_changed(e)
    if java2int(e.buttonL) == 0
        fprintf("Left button pressed\n");
    else
        fprintf("Left button released\n");
    end
    if java2int(e.buttonR) == 0
        fprintf("Right button pressed\n");
    else
        fprintf("Right button released\n");
    end
    fprintf("\n");
end

function int = java2int(value)
    if compare_versions(version(), "3.8", "<=")
        int = value.intValue();
    else
        int = value;
    end
end
