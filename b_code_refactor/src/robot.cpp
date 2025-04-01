#include "robot.hpp"
#include <iostream>
#include <thread>
#include <cmath>

using namespace std;  // Remove the need for std::, like in original code.

#define M_PI 3.14159265358979323846

// Constructor: Initialize robot state, starting a facing positive X
Robot::Robot() : battery(MAX_BATTERY), isCharging(false), motorState(false), 
                odomX(0.0), odomY(0.0), angle(0.0) {}

void Robot::simulateProcessingTime(double durationSeconds) {
    this_thread::sleep_for(chrono::milliseconds(
        static_cast<int>(durationSeconds * PROCESS_TIME)));
}

// Update the battery level based on distance and speed
void Robot::updateBatteryLevel(double value, double speed, bool isTurning) {
    if (isTurning) {
        battery -= static_cast<int>(BATTERY_DRAIN_TURNING);  // Fixed cost for turning
    } else {
        battery -= static_cast<int>(value * BATTERY_DRAIN_FACTOR * speed);  // Linear movement
    }
    cout << "Battery level updated to: " << battery << endl;
    checkBattery();
}

// Function to check the battery
void Robot::checkBattery() {
    if (battery <= 0) {
        cout << "Error: Battery Empty! Charging..." << endl;
        // Charge to Full
        // NOTE: Incase of emergency maybe its best not to charge to full as
        // you are in a rush to complete task... something worth thinking about.
        while (battery < MAX_BATTERY) {
            chargeBattery();
        }
    } else if (battery < LOW_BATTERY_THRESHOLD) {
        cout << "Warning: Battery Low!" << endl;
    }
}

// Move the robot forward
void Robot::moveRobotForward(double distance, double speed) {
    motorState = true;
    updateBatteryLevel(distance, speed, false);
    // Convert angle to radians for sin/cos
    double radians = angle * M_PI / 180.0;
    double newX = odomX + distance * cos(radians);
    double newY = odomY + distance * sin(radians);
    updateOdometry(newX, newY);
    simulateProcessingTime(distance / speed);
    cout << "Moved forward " << distance << " meters at speed " << speed << " m/s" << endl;
    motorState = false;
}

// Note: Now that we can turn. will we still need to go backwards?
// Thinking: I not sure what tools are attached to the robot like what the front
// has compared to the back.
// Solution: use moveRobotBackward when the target is roughly behind the robot.
// Move the robot backwards
void Robot::moveRobotBackward(double distance, double speed) {
    motorState = true;
    updateBatteryLevel(distance, speed, false);
    double radians = angle * M_PI / 180.0;
    double newX = odomX - distance * cos(radians);
    double newY = odomY - distance * sin(radians);
    updateOdometry(newX, newY);
    simulateProcessingTime(distance / speed);
    cout << "Moved backward " << distance << " meters at speed " << speed << " m/s" << endl;
    motorState = false;
}

// Note: Completed Extra request
// Turn/Move the robot right
void Robot::moveRobotRight(double angleDegrees, double speed) {
    motorState = true;
    updateBatteryLevel(0, speed, true);  // 0 distance, true for turning, Small Battery cost for turning
    angle -= round(angleDegrees);    // Turn right decreases angle
    if (angle < 0) angle += 360;  // Keep angle between 0-360
    simulateProcessingTime(angleDegrees / speed);  // Time needed to turn  90/90 = 1 so a bit fast
    cout << "Turned right " << round(angleDegrees) << " degrees at speed " << speed << " deg/s, new angle: " << angle << endl;
    motorState = false;
}

// Turn/Move the robot right
void Robot::moveRobotLeft(double angleDegrees, double speed) {
    motorState = true;
    updateBatteryLevel(0, speed, true);  // 0 distance, true for turning, Small battery cost for turning
    angle += round(angleDegrees);    // Turn left increases angle
    if (angle >= 360) angle -= 360;  // Keep angle between 0-360
    simulateProcessingTime(angleDegrees / speed);  // Time needed to turn
    cout << "Turned left " << round(angleDegrees) << " degrees at speed " << speed << " deg/s, new angle: " << angle << endl;
    motorState = false;
}

// Charge the Battery
void Robot::chargeBattery() {
    isCharging = true;
    battery = min(MAX_BATTERY, battery + 10);
    simulateProcessingTime(BATTERY_CHARGE_TIME_FACTOR);
    cout << "Charging... Battery at: " << battery << endl;
    isCharging = false;
}

// Update the odometry
void Robot::updateOdometry(double x, double y) {
    odomX = x;
    odomY = y;
    cout << "Odometry updated to (" << x << ", " << y << ")" << endl;
}

// Get the current odometry
double* Robot::getOdometry() const {
    double* pos = new double[2];
    pos[0] = odomX;
    pos[1] = odomY;
    return pos;
}

// Calculate distance to goal
double Robot::calculateDistance(double targetX, double targetY) const {
    double dx = targetX - odomX;
    double dy = targetY - odomY;
    return sqrt(dx * dx + dy * dy);  // sqrt() never returns negative as we need Hypotenuse
}

// Process each task
bool Robot::processTask(double targetX, double targetY, double moveSpeed, double turnSpeed) {
    printTaskStart(targetX, targetY);
    bool taskCompleted = false;
    
    // Keep trying until the task is completed
    while (!taskCompleted) {
        // Charge if battery is low before starting or resuming
        while (battery < LOW_BATTERY_THRESHOLD) {
            chargeBattery();
        }

        // Attempt to reach the target
        // Note: I thought about using as PID control loop as to control how the robot will 
        // target and drive to the desired location however its a bit tricky to implement in c++
        // for me and i think it might be out of scope for this project.
        while (calculateDistance(targetX, targetY) > TOLERANCE) {
            double* currentPos = getOdometry();
            double dx = targetX - currentPos[0];
            double dy = targetY - currentPos[1];
            delete[] currentPos;

            // Simple navigation: turn then move
            double targetAngle = atan2(dy, dx) * 180 / M_PI;
            // Note: If use 3.145.. there will be floating-point precision errors.
            if (targetAngle < 0) targetAngle += 360;
            
            double angleDiff = targetAngle - angle;
            if (angleDiff > 180) angleDiff -= 360;
            else if (angleDiff < -180) angleDiff += 360;

            double absAngleDiff = abs(angleDiff);
            // If target is roughly behind, move backward
            if (absAngleDiff > MIN_DEGREE_LIMIT && absAngleDiff < MAX_DEGREE_LIMIT) {
                double distance = calculateDistance(targetX, targetY);
                moveRobotBackward(min(1.0, distance), moveSpeed);
            }
            // Otherwise, turn and move forward
            else if (absAngleDiff > 5) { // 5-degree tolerance
                double turn = min(MAX_DEGREE_TURN, absAngleDiff);
                if (angleDiff > 0) moveRobotLeft(turn, turnSpeed);
                else moveRobotRight(turn, turnSpeed);
            }
            else {
                double distance = calculateDistance(targetX, targetY);
                moveRobotForward(min(1.0, distance), moveSpeed);
            }
            // If battery runs out, break inner loop to charge, but outer loop will retry
            if (battery <= 0) {
                break;
            }
        }
        // Check if we reached the target
        if (calculateDistance(targetX, targetY) <= TOLERANCE) {
            updateOdometry(targetX, targetY);  // Added for precision)
            taskCompleted = true;
        }
        // If we didn't reach it (due to battery), we'll charge and retry
    }

    return true;  // Task is guaranteed to complete -- hopefully
}

void Robot::printStatus() const {
    double* pos = getOdometry();
    cout << "\n--- Robot Status ---" << endl;
    cout << "\nCurrent position: (" << pos[0] << ", " << pos[1] << ")\n";
    cout << "Battery level: " << battery << "\n";
    cout << "Current Orientation: " << angle << "°\n";
    cout << "---------------------" << endl;
    delete[] pos;
}

void Robot::printTaskStart(double targetX, double targetY) const {
    cout << "\n--- Starting New Task ---" << endl;
    cout << "Current Position: (" << odomX << ", " << odomY << ")" << endl;
    cout << "Target Position: (" << targetX << ", " << targetY << ")" << endl;
    cout << "------------------------" << endl;
}

// Set the Battery level  -- exists be never used
void Robot::setBatteryLevel(int b) {
    battery = b;
    cout << "Battery set to: " << battery << endl;
}