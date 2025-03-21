# Section B: Code Refactor

In this assessment, we want to verify your skill in reading and understanding code, as well as relating it to physical systems. After all, we work with real robots. Treat this code as a general base for a virtual robot’s functionality, but feel free to refactor it as much as you believe is necessary. The goal is to ensure it is deploy-worthy and can be maintained for years to come.

In the `src` folder, you will find a `.cpp` file that contains methods to move a robot around a fantasy world. This code was written by a fairly new programmer in a rush. Your tasks are as follows:

- Refactor the code so that the simulated robot behaves as closely as possible to a real robot, avoiding any undefined or strange behaviour.
- Implement a method to process tasks given to the robot. Since it's a simulation of a physical robot, each task should require some processing time to finish.
- In the `main` method, create tasks that move the robot from its initial position to `[0,0]`, then on to the following positions:
  - `[20,0]`
  - `[20,20]`
  - `[-20,20]`
  - `[-20,-20]`
  - `[20,-20]`

After each command, the robot’s battery level and current odometry position should be printed to the terminal. Ensure the robot does not run out of battery at any point.

## Extra

For an extra (optional) task, modify the move-right and move-left methods to turn the robot by a certain angle instead of moving it laterally.

---

# How to Build the Code

1. Create a `build` directory:

  ```bash
  mkdir build && cd build
  ```
Generate the Makefile:
  ```bash
  cmake ..
  ```
Compile
  ```bash
  make
  ```
Run:
  ```bash
  ./robot_brain
  ```
