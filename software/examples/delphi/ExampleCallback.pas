program ExampleCallback;

{$ifdef MSWINDOWS}{$apptype CONSOLE}{$endif}
{$ifdef FPC}{$mode OBJFPC}{$H+}{$endif}

uses
  SysUtils, IPConnection, BrickletDualButtonV2;

type
  TExample = class
  private
    ipcon: TIPConnection;
    db: TBrickletDualButtonV2;
  public
    procedure StateChangedCB(sender: TBrickletDualButtonV2; const buttonL: byte;
                             const buttonR: byte; const ledL: byte; const ledR: byte);
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = 'XYZ'; { Change XYZ to the UID of your Dual Button Bricklet 2.0 }

var
  e: TExample;

{ Callback procedure for state changed callback }
procedure TExample.StateChangedCB(sender: TBrickletDualButtonV2; const buttonL: byte;
                                  const buttonR: byte; const ledL: byte;
                                  const ledR: byte);
begin
  if (buttonL = BRICKLET_DUAL_BUTTON_V2_BUTTON_STATE_PRESSED) then begin
    WriteLn('Left Button: Pressed');
  end
  else if (buttonL = BRICKLET_DUAL_BUTTON_V2_BUTTON_STATE_RELEASED) then begin
    WriteLn('Left Button: Released');
  end;

  if (buttonR = BRICKLET_DUAL_BUTTON_V2_BUTTON_STATE_PRESSED) then begin
    WriteLn('Right Button: Pressed');
  end
  else if (buttonR = BRICKLET_DUAL_BUTTON_V2_BUTTON_STATE_RELEASED) then begin
    WriteLn('Right Button: Released');
  end;

  WriteLn('');
end;

procedure TExample.Execute;
begin
  { Create IP connection }
  ipcon := TIPConnection.Create;

  { Create device object }
  db := TBrickletDualButtonV2.Create(UID, ipcon);

  { Connect to brickd }
  ipcon.Connect(HOST, PORT);
  { Don't use device before ipcon is connected }

  { Register state changed callback to procedure StateChangedCB }
  db.OnStateChanged := {$ifdef FPC}@{$endif}StateChangedCB;

  { Enable state changed callback }
  db.SetStateChangedCallbackConfiguration(true);

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
