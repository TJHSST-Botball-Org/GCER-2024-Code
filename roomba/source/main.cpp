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
    
    wait_for_light(5);
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
    msleep(1500);

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
    msleep(1500);
    robot.halt();

    robot.drive_direct(100, -100); //cw
    //MADE CHANGE TO TURN VALUE, ORIGINAL 800
    msleep(800); // Turn 45 deg CW
    robot.halt();

    robot.set_distance(0);
    robot.move_straight(-100);
    msleep(5175);
    robot.halt();
    std::cout << robot.get_distance() << std::flush;
    std::cout << "\n" << std::flush;
    // Step 4: Turn left and push everything into the rock pit

    out("Step 4: Turn left and push everything into the rock pit");

    robot.drive_direct(-100, 100); //ccw
    msleep(2200); // 
    
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

    robot.move_straight(-100);
    msleep(4000); // moving towards the center of the board

    robot.halt();
    robot.move_straight(0);
    robot.cup_arm_retract();
    robot.move_straight(-100);
    msleep(4000);
    robot.line_up_with_black_line(-100);








    robot.drive_direct(-100, 100); //ccw
    msleep(1600);
    robot.halt();

    robot.move_straight(100);

    while (robot.get_left_bump() == 0 && robot.get_right_bump() == 0)
    {
        msleep(1);
    }

    robot.halt();


    // We are going to move south a bit to get rid of the second poms pile
    robot.move_straight(-200);
    msleep(2200);
    robot.halt();

    
    
    
    
    // Bumping into the moon base/tower so that we align ourselves
    // Then move south to get in line in the middle on the up and
    // down axis.
    
    robot.move_straight(100);

    while (robot.get_left_bump() == 0 && robot.get_right_bump() == 0)
    {
        msleep(1);
    }
    robot.halt();


    robot.move_straight(-100);
    msleep(1578); // This number controls how much on the up and down axis
                  // to move back. This will align your robot
                  // on the up and down axis
                  // 1578 / (2000/9) = 7.1 inches
                  // Units are: ms / (ms/inch)
    robot.halt();

    // Rotating so that the front faces east
    robot.drive_direct(100, -100); //cw
    msleep(1600);
    robot.halt();

    // We are now in the middle of the board, aligned on the north-south axis
    // We are facing east
    // However, we still need to align on the east-west axis

    // First, we move east four inches, so that the switch arm won't hit anything
    robot.move_straight(100);
    msleep(889); // 889 = 4 inch * (2000/9)
    robot.halt();

    // We then extend the switch
    robot.extend_switch_arm();
    msleep(1000); // Give it some time to extend

    // Then we can move forward 2.5 inches so that everything is aligned
    robot.move_straight(-100);
    msleep(556); // 556 = 2.5 * (2000/9)

    // The robot is now facing east, and is aligned on both north-south 
    // and east-west axis.
     

    // Step 8: Get the arms ready, flick the switch
    out("Step 8: Get the arms ready, flick the switch");
    robot.cup_arm_right();
    msleep(1500);
    robot.close_cup_gate();
    
    // Flicking the switch
    // Arm should already be extended
    robot.flick_switch();
    msleep(1000);
    robot.cup_arm_shake();




    
    // Step 9: Go down, hit the wall
    out("Step 9");
    robot.slow_cup_arm_retract();
    robot.drive_direct(100, -100); //cw
    msleep(1600);
    robot.move_straight(100);
    while (robot.get_left_bump() == 0 && robot.get_right_bump() == 0)
    {
        msleep(1);
    }
    robot.halt();

    
    
    robot.move_straight(-400);
    msleep(1000);
    
    

    // Step 10: Turn CCW, bump into the lava tube pit
    out("Step 10");
    robot.drive_direct(-100, 100); //ccw
    msleep(1600);

    robot.move_straight(100);
    msleep(400);
    
    robot.line_up_with_black_line(-200);
    robot.halt();
    
    robot.move_straight(100);
    msleep(2000);
    
    robot.arm_retract(553);
    
    //while (robot.get_left_bump() == 0 && robot.get_right_bump() == 0)
    //{
    //    msleep(1);
    //}
    //robot.halt();

    
    //robot.halt();

    //robot.drive_direct(-100, 100); //ccw
    //msleep(675);
    //robot.halt();
    //robot.slow_cup_arm_forward();

    //msleep(1000);
    //robot.open_cup_gate();
    //msleep(500);

    // Shake
    robot.close_cup_gate();
    msleep(500);
    robot.open_cup_gate();
    msleep(500);
    robot.close_cup_gate();
    msleep(500);
    robot.open_cup_gate();

    set_servo_position(2, 641);
    msleep(5000);

    return 0;

// 763 and 554
}
