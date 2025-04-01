#include "robot.hpp"
#include <vector>
#include <utility>

// Keeping Main as thin as possible.
int main() {
    // Create the robot
    Robot myRobot;

    // Define a list of target positions
    std::vector<std::pair<double, double>> tasks = {
        {0, 0},
        {20, 0},
        {20, 20},
        {-20, 20},
        {-20, -20},
        {20, -20}
    };
    // TODO: Maybe add a file reader instead but Im not sure how to do it in C++ very well.

    // Process each task in order. 
    // Im not passing speed of robot for movement and turning as I want to treat this as a test file.
    for (auto& task : tasks) {
        myRobot.processTask(task.first, task.second);
        myRobot.printStatus();
    }

    return 0;
}