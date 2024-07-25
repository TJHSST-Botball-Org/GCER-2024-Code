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

    robot.set_distance(0);

    robot.drive_direct(-100, 100); //ccw-
    msleep(1600);

    while (robot.get_left_bump() != 1 && robot.get_right_bump() != 1)
    {
        robot.move_straight(50);
    }

    robot.drive_direct(100, -100); //cw
    msleep(1400);

    out("Step 1: Move until black line");

    robot.set_distance(0);
    //robot.drive_direct(50, 0);
    //msleep(1000);
    //robot.move_straight(-50);

    out("Waiting for black line...");

    robot.line_up_with_black_line(-100);

    out("Detected black line. Left value: " + std::to_string(robot.get_far_left_cliff()) + " Right value: " + std::to_string(robot.get_far_right_cliff()));

    
    out("lined up");
    
    robot.move_straight(-100);
    msleep(3000);
    robot.drive_direct(-100, 100);
    msleep(183);

    out("Waiting for second black line...");

    robot.line_up_with_black_line(-100);

    out("Detected second black line. Left value: " + std::to_string(robot.get_far_left_cliff()) + " Right value: " + std::to_string(robot.get_far_right_cliff()));
    out("lined up");

    robot.halt();

   

    // 2. Turn left, go up

    out("Step 2: Turn left, go up");

    // Turn slightly, back up, then turn all the way
    robot.cup_arm_right();
    robot.set_distance(0);
    robot.drive_direct(-100, 100); //ccw
    msleep(800);
    robot.halt();
    robot.move_straight(50);
    msleep(1000);
    robot.halt();
    robot.drive_direct(-100, 100); //ccw
    msleep(800);

    while (robot.get_left_bump() != 1 && robot.get_right_bump() != 1)
    {
        robot.move_straight(100);
    }

    robot.set_distance(0);
    robot.move_straight(-100);
    msleep(2159);
    robot.halt();
    robot.cup_arm_retract(); // Retract half way so that we don't collide
                             // with the small robot

    // Moving north
    robot.move_straight(-100);
    msleep(1850);
    robot.halt();

    // 3. Turn right, go right

    out("Step 3: Turn right, go right");


    // When turning right, turn 45 degs, back up a bit, then turn 45 degs
    // This is so that we don't miss the first orange pom
    robot.drive_direct(100, -100); //cw
    msleep(800);
    robot.halt();

    robot.set_distance(0);

    robot.drive_direct(100, -100); //cw
    msleep(800);
    robot.halt();

    robot.set_distance(0);
    // Line up with the black line
    robot.center_cliff_line_up_with_black_line(-100);

    robot.drive_direct(-100, 100); //ccw
    msleep(800); // Turn 45 deg CCW
    robot.halt();

    robot.move_straight(-100);
    msleep(2000);
    robot.halt();

    robot.drive_direct(100, -100); //cw
    msleep(600); // Turn 45 deg CW
    robot.halt();

    robot.set_distance(0);
    robot.move_straight(-100);
    msleep(5500);
    robot.halt();
    std::cout << robot.get_distance() << std::flush;
    std::cout << "\n" << std::flush;
    // Step 4: Turn left and push everything into the rock pit

    out("Step 4: Turn left and push everything into the rock pit");

    robot.drive_direct(-100, 100); //ccw
    msleep(2200); // 120 deg
    
    robot.halt();
    
    robot.drive_direct(100, -100); //cw
    msleep(600);
    

    robot.move_straight(-100);
    msleep(1000);

    // Step 5: Drive and bump into the lava tube pit
    out("Step 5: Drive and bump into the lava tube pit");
    robot.move_straight(100);

    while (robot.get_left_bump() == 0 && robot.get_right_bump() == 0)
    {
        msleep(1);
    }

    robot.halt();
    
    // Line up again at the rock pit black line
    robot.line_up_with_black_line(-100);

    // Drive again and bump into the lava tube pit

    robot.move_straight(100);

    while (robot.get_left_bump() == 0 && robot.get_right_bump() == 0)
    {
        msleep(1);
    }
    
    // Step 6: Back up slightly
    out("Step 6: Back slightly");
    robot.move_straight(-100);
    msleep(1270);

    robot.halt();

    robot.cup_arm_forward();

    // Step 7: Rotate ccw, then move backwards until black line. We are then aligned with the pool noodles.
    out("Step 7: Rotate ccw, then move backwards until black line. We are then aligned with the pool noodles.");
    robot.drive_direct(-100, 100); //ccw
    msleep(1700);
    robot.halt();

	// robot.extend_switch_arm();
    robot.move_straight(-100);
    msleep(4000); // moving towards the center of the board

    robot.halt();
    robot.cup_arm_retract();
    robot.move_straight(-100);
    msleep(4000);



    robot.drive_direct(-100, 100); //ccw
    msleep(1600);
    robot.halt();

    robot.move_straight(100);

    while (robot.get_left_bump() == 0 && robot.get_right_bump() == 0)
    {
        msleep(1);
    }

    robot.halt();

    robot.move_straight(-100);
    msleep(1800);


    robot.drive_direct(100, -100); //cw
    msleep(1450);
    robot.halt();

    robot.extend_switch_arm();
    msleep(1000);

    robot.move_straight(-100);
    msleep(850);

    robot.halt();
    return 0;

    // Move forward slightly
    // robot.move_straight(100);
    // msleep(1250); 


    // Step 8: Get the arms ready, flick the switch
    out("Step 8: Get the arms ready, flick the switch");
    robot.cup_arm_right();
    robot.close_cup_gate();
    
    // Flicking the switch
    robot.extend_switch_arm();
    robot.flick_switch();


    // Step 9: Pool noodle should be in the cup; start moving to the lava pits
    out("Step 9: Pool noodle should be in the cup; start moving to the lava pits");
    robot.retract_switch_arm();
    robot.move_straight(100);
    msleep(1000);
    robot.cup_arm_forward();
    
    // Step 10: Turn towards the south wall, bump into it to align
    out("Step 10: Turn towards the south wall, bump into it to align");
    robot.drive_direct(100, -100); //cw
    msleep(1600);
    robot.move_straight(50);
    while (robot.get_left_bump() == 0 && robot.get_right_bump() == 0)
    {
        msleep(1);
    }
    robot.drive_direct(-100, 100); //ccw
    msleep(1600);

    // Step 11: Move towards the lava tube pits until we bump into it
    out("Step 11: Move towards the lava tube pits until we bump into it");
    robot.move_straight(100);
    while (robot.get_left_bump() == 0 && robot.get_right_bump() == 0)
    {
        msleep(1);
    }

    // Step 12: Drop the pool noodles
    out("Step 12: Drop the pool noodles");
    robot.open_cup_gate();

    // More to do I guess later on but for now it works
}
