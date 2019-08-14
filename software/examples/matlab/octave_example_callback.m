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

    % Enable state changed callback
    db.setStateChangedCallbackConfiguration(true);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for state changed callback
function cb_state_changed(e)
    if e.buttonL == 0
        fprintf("Left Button: Pressed\n");
    elseif e.buttonL == 1
        fprintf("Left Button: Released\n");
    end

    if e.buttonR == 0
        fprintf("Right Button: Pressed\n");
    elseif e.buttonR == 1
        fprintf("Right Button: Released\n");
    end

    fprintf("\n");
end
