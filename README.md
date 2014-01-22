# rbServo Readme

### What is it?
All the hardware and software that is needed to build a CAN-BUS servo controller. It is meant to be used for RC servos.

### What does it contain?

- `HW` - all the hardware design files are in this folder

  - `Final` contains the final layout, fits in a standard RC servo

  - `Proto` contains a more debug-friendly layout. Fits on your desktop.

  - `Common` contains files that are shared between the `Final` and `Proto` KiCad projects. Usually there is no need to edit them.

- `SW` - The software for the servo.
 - `rbServoFirmware`
 - `rbServoBoot`