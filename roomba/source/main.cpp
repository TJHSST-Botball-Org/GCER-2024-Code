#include "Create.h"

#ifndef IS_KIPR_INCLUDED
#define IS_KIPR_INCLUDED 1
#include <kipr/kipr.h>
#endif

#include <iostream>
#include <string>

void out(std::string content)
{
    std::cout << content + "\n" << std::flush;
}

int main()
{
    Create robot;
    
    //wait_for_light();

    shut_down_in(119);

    /* MOVING THE ROCKS*/

    // 1. Move until black line

    out("Step 1: Move until black line");

    robot.set_distance(0);
    robot.move_straight(-300);

    out("Waiting for black line...");
    while (robot.get_far_left_cliff() > Create::CLIFF_SENSOR_THRESHOLD && robot.get_far_right_cliff() > Create::CLIFF_SENSOR_THRESHOLD)
    {
        out("Waiting " + std::to_string(robot.get_far_left_cliff()) + " " + std::to_string(robot.get_far_right_cliff()));
        msleep(1);
    }

    out("Detected black line. Left value: " + std::to_string(robot.get_far_left_cliff()) + " Right value: " + std::to_string(robot.get_far_right_cliff()));

    out("Waiting for second black line...");

    while (robot.get_far_left_cliff() > Create::CLIFF_SENSOR_THRESHOLD && robot.get_far_right_cliff() > Create::CLIFF_SENSOR_THRESHOLD)
    {
        out("Waiting " + std::to_string(robot.get_far_left_cliff()) + " " + std::to_string(robot.get_far_right_cliff()));
        msleep(1);
    }

    out("Detected second black line. Left value: " + std::to_string(robot.get_far_left_cliff()) + " Right value: " + std::to_string(robot.get_far_right_cliff()));

    robot.halt();

    // 2. Turn left, go up
/*
    out("Step 2: Turn left, go up");

    this->set_distance(0);
    robot.spin_block(300, -90);

    this->set_distance(0);
    robot.move_straight(300);

    out("Step 2 Waiting for black line...");

    while (robot.get_far_left_cliff() > Create::CLIFF_SENSOR_THRESHOLD && robot.get_far_right_cliff() > Create::CLIFF_SENSOR_THRESHOLD)
    {
        out("Waiting " + std::to_string(robot.get_far_left_cliff()) + " " + std::to_string(robot.get_far_right_cliff()));
        msleep(1);
    }

    out("Step 2 Detected black line. Left value: " + std::to_string(robot.get_far_left_cliff()) + " Right value: " + std::to_string(robot.get_far_right_cliff()));

    robot.halt();

    // 3. Turn right, go right

    out("Step 3: Turn right, go right");

    this->set_distance(0);
    robot.spin_block(300, 90);

    this->set_distance(0);
    robot.move_straight(300);

    // Stop at Area 4 and Rock Heap vertical black line

    out("Step 3 Waiting for black line...");

    while (robot.get_far_left_cliff() > Create::CLIFF_SENSOR_THRESHOLD && robot.get_far_right_cliff() > Create::CLIFF_SENSOR_THRESHOLD)
    {
        out("Waiting " + std::to_string(robot.get_far_left_cliff()) + " " + std::to_string(robot.get_far_right_cliff()));
        msleep(1);
    }

    out("Step 3 Detected black line. Left value: " + std::to_string(robot.get_far_left_cliff()) + " Right value: " + std::to_string(robot.get_far_right_cliff()));

    robot.halt();

    
    // Step 4
*/
    

}
