Imports System
Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your Dual Button Bricklet 2.0

    ' Callback subroutine for state changed callback
    Sub StateChangedCB(ByVal sender As BrickletDualButtonV2, ByVal buttonL As Byte, _
                       ByVal buttonR As Byte, ByVal ledL As Byte, ByVal ledR As Byte)
        If buttonL = BrickletDualButtonV2.BUTTON_STATE_PRESSED Then
            Console.WriteLine("Left Button: Pressed")
        Else If buttonL = BrickletDualButtonV2.BUTTON_STATE_RELEASED Then
            Console.WriteLine("Left Button: Released")
        End If

        If buttonR = BrickletDualButtonV2.BUTTON_STATE_PRESSED Then
            Console.WriteLine("Right Button: Pressed")
        Else If buttonR = BrickletDualButtonV2.BUTTON_STATE_RELEASED Then
            Console.WriteLine("Right Button: Released")
        End If

        Console.WriteLine("")
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim db As New BrickletDualButtonV2(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Register state changed callback to subroutine StateChangedCB
        AddHandler db.StateChangedCallback, AddressOf StateChangedCB

        ' Enable state changed callback
        db.SetStateChangedCallbackConfiguration(True)

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
