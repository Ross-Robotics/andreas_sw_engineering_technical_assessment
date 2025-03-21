#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

// Global variables
int battery = 100;
bool isCharging = false;
bool motorState = false;
double lastOdomX = 0.0, lastOdomY = 0.0;

// command Struct
struct Command {
    string type;
    double value;
};

// Function to check the battery
void checkBattery() {
    if (battery < 20) {
        cout << "Warning: Battery Low!" << endl;
    }
    if (battery == 0) {
        cout << "Error: Battery Empty!" << endl;
    }
}

// Move the robot forward
void moveRobotForward(double distance, double speed) {
    motorState = true;
    updateBatteryLevel(distance, speed);
    updateOdometry(lastOdomX + distance, lastOdomY);
    cout << "Moving forward " << distance << " meters with speed " << speed << endl;
}

// Move the robot backwards
void moveRobotBackward(double distance, double speed) {
    motorState = true;
    updateBatteryLevel(distance, speed);
    updateOdometry(lastOdomX - distance, lastOdomY);
    cout << "Moving backward " << distance << " meters with speed " << speed << endl;
}

// Move robot to the right
void moveRobotRight(double distance, double speed) {
    motorState = true;
    updateBatteryLevel(distance, speed);
    updateOdometry(lastOdomX, lastOdomY + distance);
    cout << "Moving right " << distance << " meters with speed " << speed << endl;
}

// Move robot to the left
void moveRobotLeft(double distance, double speed) {
    motorState = true;
    updateBatteryLevel(distance, speed);
    updateOdometry(lastOdomX, lastOdomY - distance);
    cout << "Moving left " << distance << " meters with speed " << speed << endl;
}

// Get the current odometry
double* getOdometry() {
    double* pos = new double[2];
    pos[0] = lastOdomX;
    pos[1] = lastOdomY;
    return pos;
}

// Update the odometry
void updateOdometry(double x, double y) {
    lastOdomX = x;
    lastOdomY = y;
    cout << "Odometry updated to (" << x << ", " << y << ")" << endl;
}

// Calculate distance to goal
double calculateDistance(double targetX, double targetY) {
    double result = lastOdomX + lastOdomY - (targetX + targetY);
    return (result > 0) ? result : -result;
}

// Set the Battery level
void setBatteryLevel(int b) {
    battery = b;
    cout << "Battery set to: " << battery << endl;
}

// Update the battery level based on distance and speed
void updateBatteryLevel(double distance, double speed) {
    battery -= distance * speed;
    cout << "Battery level updated to: " << battery << endl;
}

// Charge the Battery
void chargeBattery() {
    isCharging = true;
    battery++;
    cout << "Charging..." << endl;
}

int main() {

    return 0;
}
