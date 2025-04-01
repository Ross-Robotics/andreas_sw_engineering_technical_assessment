#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <string>
#include <vector>
#include <chrono>

class Robot {
private:
    static constexpr int LOW_BATTERY_THRESHOLD = 20;
    static constexpr int MAX_BATTERY = 100;
    static constexpr double BATTERY_DRAIN_FACTOR = 2.0;  // Battery units per meter
    static constexpr double TOLERANCE = 0.1;  // Level of accuracy
    static constexpr double MIN_DEGREE_LIMIT = 150.0;
    static constexpr double MAX_DEGREE_LIMIT = 190.0;
    static constexpr double MAX_DEGREE_TURN = 45.0;  // Simulate Robot Turning Limit
    static constexpr double BATTERY_DRAIN_TURNING = 1.0;
    static constexpr double BATTERY_CHARGE_TIME_FACTOR = 0.5;  // Renamed for consistency
    static constexpr double PROCESS_TIME = 100.0;
    static constexpr double SPEED = 1.0; // Driving Speed m.s and turning
    static constexpr double TURNING_SPEED = 90.0; // Truning Speed m.s and turning

    int battery;
    bool isCharging;
    // Would Use a State machine but this will do for now.
    bool motorState;
    double odomX;
    double odomY;
    double angle;

    void updateBatteryLevel(double distance, double speed, bool isTurning = false);
    void simulateProcessingTime(double durationSeconds);
    void printTaskStart(double targetX, double targetY) const;
public:
    // I created the Command but I cant think of a way to use/need this struct
    // here because it was in original code.
    struct Command {
        std::string type;
        double value;
        Command(std::string t, double v) : type(t), value(v) {}
    };

    Robot();
    // Turns right by degrees -- extra
    // Movement functions
    void moveRobotForward(double distance, double speed); 
    void moveRobotBackward(double distance, double speed);
    void moveRobotRight(double angleDegrees, double speed);
    void moveRobotLeft(double angleDegrees, double speed);
    
    // State management
    void chargeBattery();
    void checkBattery();
    void updateOdometry(double x, double y);
    double* getOdometry() const;
    double calculateDistance(double targetX, double targetY) const;
    
    // Task processing
    void setBatteryLevel(int b);
    bool processTask(double targetX, double targetY, double moveSpeed = SPEED, double turnSpeed = TURNING_SPEED);
    int getBatteryLevel() const { return battery; }
    void printStatus() const;
};

#endif