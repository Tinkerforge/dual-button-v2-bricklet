#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletDualButtonV2;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Dual Button Bricklet 2.0

# Callback subroutine for state changed callback
sub cb_state_changed
{
    my ($button_l, $button_r, $led_l, $led_r) = @_;

    if ($button_l == Tinkerforge::BrickletDualButtonV2->BUTTON_STATE_PRESSED)
    {
        print "Left Button: Pressed\n";
    }
    elsif ($button_l == Tinkerforge::BrickletDualButtonV2->BUTTON_STATE_RELEASED)
    {
        print "Left Button: Released\n";
    }

    if ($button_r == Tinkerforge::BrickletDualButtonV2->BUTTON_STATE_PRESSED)
    {
        print "Right Button: Pressed\n";
    }
    elsif ($button_r == Tinkerforge::BrickletDualButtonV2->BUTTON_STATE_RELEASED)
    {
        print "Right Button: Released\n";
    }

    print "\n";
}

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $db = Tinkerforge::BrickletDualButtonV2->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register state changed callback to subroutine cb_state_changed
$db->register_callback($db->CALLBACK_STATE_CHANGED, 'cb_state_changed');

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
