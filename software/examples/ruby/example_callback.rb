#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_dual_button_v2'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your Dual Button Bricklet 2.0

ipcon = IPConnection.new # Create IP connection
db = BrickletDualButtonV2.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Register state changed callback
db.register_callback(BrickletDualButtonV2::CALLBACK_STATE_CHANGED) do |button_l, button_r,
                                                                       led_l, led_r|
  if button_l == BrickletDualButtonV2::BUTTON_STATE_PRESSED
    puts "Left Button: Pressed"
  elsif button_l == BrickletDualButtonV2::BUTTON_STATE_RELEASED
    puts "Left Button: Released"
  end

  if button_r == BrickletDualButtonV2::BUTTON_STATE_PRESSED
    puts "Right Button: Pressed"
  elsif button_r == BrickletDualButtonV2::BUTTON_STATE_RELEASED
    puts "Right Button: Released"
  end

  puts ''
end

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
