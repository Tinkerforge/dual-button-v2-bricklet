function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletDualButtonV2;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Dual Button Bricklet 2.0

    ipcon = IPConnection(); % Create IP connection
    db = handle(BrickletDualButtonV2(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register state changed callback to function cb_state_changed
    set(db, 'StateChangedCallback', @(h, e) cb_state_changed(e));

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end

% Callback function for state changed callback
function cb_state_changed(e)
    if e.buttonL == com.tinkerforge.BrickletDualButtonV2.BUTTON_STATE_PRESSED
        fprintf('Left Button: Pressed\n');
    elseif e.buttonL == com.tinkerforge.BrickletDualButtonV2.BUTTON_STATE_RELEASED
        fprintf('Left Button: Released\n');
    end

    if e.buttonR == com.tinkerforge.BrickletDualButtonV2.BUTTON_STATE_PRESSED
        fprintf('Right Button: Pressed\n');
    elseif e.buttonR == com.tinkerforge.BrickletDualButtonV2.BUTTON_STATE_RELEASED
        fprintf('Right Button: Released\n');
    end

    fprintf('\n');
end
