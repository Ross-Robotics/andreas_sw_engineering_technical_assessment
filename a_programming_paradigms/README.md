# Section A: Programming Paradigms

Implement, in C++, the control logic for a media player device. The device can be either **On** or **Off**. When the device is switched on, it can be either: **Playing**, **Paused**, or **Stopped**. The device should respond to the following inputs:

- **Power Button Pressed**: Toggles the device between Off and On.
- **Play/Pause Button Pressed**: When in Stopped or Paused mode, the device should transition to Playing. When in - Playing mode, it should transition to Paused.
**Stop Button Pressed**: When in Playing or Paused mode, the device should transition to Stopped.

Your implementation does **not** need to handle audio - we are specifically interested in your approach to implementing the control logic. Inputs should be processed from input to the terminal.

Ensure that the system prevents any undefined behavior. Additional credit will be awarded for implementations that are structured to allow for easy extension and integration of new states.

![diagram](https://github.com/user-attachments/assets/cdfc0ea4-5512-4a5b-9b15-9d56838b73a3)
