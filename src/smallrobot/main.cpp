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
	//move out of starting area
	robot.moveDistanceAndCorrect(3, 800); 
	//turn towards poms
	robot.rotateAndCorrect(-45.0, 800);
	//move to poms
	robot.moveDistanceAndCorrect(3, 800);
	//flick the top green pom
	robot.setFlicker(800);
	//move to get bottom red poms in plom
	robot.moveDistanceAndCorrect(2, 800);
	//spin to face north
	robot.rotate(135.0, 800);
	//move to line up with pool noodles on ground
	robot.moveDistanceAndCorrect(6, 800);
	//turn to face pool noodes
	robot.rotate(90.0,800);
	//move to collect first 3 poms
	robot.moveDistanceAndCorrect(8, 800);
	//slow turn towards area 2
	for (int i = 0; i < 4; ++i) 
	{
        	robot.rotate(-45.0, 300);
		robot.moveDistance(1.5,300);
    	}
	//move towards area 2
	robot.moveDistanceAndCorrect(10, 800);
	//move backwards to drop off noodles and poms; also move past black line so we can line up
	robot.moveDistanceAndCorrect(-7, 1200);
	//line up with black line between area 1 and 2
	robot.moveUntilEitherColorDetect(1200);
	//move so that we angle up with astronauts
	robot.moveDistanceAndCorrect(4, 1200);
	//turn towards astronauts
	robot.rotate(-90.0, 1200);
	//move until lined up with black line between area 2 and 3
	robot.moveUntilEitherColorDetect(1200);
	//rotate to get claw lined up with astronauts
	robot.rotate(180, 800);
	//move towards astronauts
	robot.moveDistanceAndCorrect(-4.0, 800);
	//pick up astronauts
	robot.openClaw();
	//put arm down
	robot.setArmPosition(30, 800);
	//close claw on astronauts
	robot.closeClaw();
	//bring arm up
	robot.setArmPosition(400, 200);
	//turn the robot towards the airlock
	robot.rotate(-8.0, 400);
	//move to the airlock
	robot.moveDistanceAndCorrect(14, 600);
	//grab airlock
	robot.setFlicker(400);
	//open airlock
	robot.moveDistanceAndCorrect(-4, 300);
	//ungrab airlock
	robot.setFlicker(800);
	//move away to set up turn
	robot.moveDistanceAndCorrect(-4, 600);
	//turn towards airlock
	robot.rotate(180, 300);
	//move towards airlock
	robot.moveDistanceAndCorrect(4,600);
	//release the astronauts
	robot.openClaw()
	return 0;
}
