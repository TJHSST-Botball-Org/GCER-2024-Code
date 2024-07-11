#include <iostream>
// #include "include/OpMode.hpp"
#include <smallRobot.h>
#include <kipr/wombat.h>

int main()
{
    //wait_for_light(3);
    shut_down_in(119);
	
	//    MOTOR             MOTOR                CONST                CONST            CONST                       CONST                        ANALOG            ANALOG             SERVO             SERVO            CONST              CONST               SERVO
	//int leftWheelPin, int rightWheelPin, float wheelDistance, float wheelRadius, int leftTicksPerRevolution, int rightTicksPerRevolution, int leftColorPin, int rightColorPin, int clawServoPin, int armServoPin, int leftThreshold, int rightThreshold, int flickerServoPin
    SmallRobot robot(0,                 1,                 6.5,             1.375,                       1900,                        1900,                0,                 1,                1,               0,              3800,               3800,                   2);
    //robot.set_servo_position(this->clawServoPin, 300);
    disable_servos();

    return 0;
}
