Imports System
Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your Dual Button Bricklet 2.0

    ' Callback subroutine for state changed callback
    Sub StateChangedCB(ByVal sender As BrickletDualButtonV2, ByVal buttonL As Byte, _
                       ByVal buttonR As Byte, ByVal ledL As Byte, ByVal ledR As Byte)
        If buttonL = BrickletDualButton.BUTTON_STATE_PRESSED Then
            Console.WriteLine("Left button pressed")
        Else
            Console.WriteLine("Left button released")
        End If

        If buttonR = BrickletDualButton.BUTTON_STATE_PRESSED Then
            Console.WriteLine("Right button pressed")
        Else
            Console.WriteLine("Right button released")
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

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
