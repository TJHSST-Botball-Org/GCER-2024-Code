
#pragma once

#ifndef IS_KIPR_INCLUDED
#define IS_KIPR_INCLUDED 1
#include <kipr/kipr.h>
#endif

// The Create class wraps some of the functions in libwallaby.
// The Create class uses Create 2 functions.
// Not all functions are wrapped, see https://www.kipr.org/doc/group__create.html
// for more.


class Create
{
private:

public:
    // CREATE SETTINGS HERE

    // Pins
    static const int SWITCH_ARM_PIN = 1;
    static const int CUP_ARM_PIN = 2;
    static const int CUP_GATE_PIN = 3;

    // Servo limits
    static const int CUP_ARM_RIGHT_POS = 167;
    static const int CUP_ARM_FORWARD_POS = 1024;
    static const int CUP_ARM_RETRACT_POS = 2047;
    static const int CUP_ARM_SHAKE_AMOUNT = 30;

    static const int CUP_GATE_OPEN_POS = 1070;
    static const int CUP_GATE_CLOSE_POS = 1660;

    static const int SWITCH_ARM_EXTEND_POS = 0;
    static const int SWITCH_ARM_ABOVE_SWITCH_POS = 50;
    static const int SWITCH_ARM_RETRACT_POS = 1588;

    // Sensor limits
    static const int CLIFF_SENSOR_THRESHOLD = 2000;


    Create();
    ~Create();

    // Movement

    void move_straight(int speed); // Non-blocking. Speed: mm/sec, -500 to 500
    void drive_direct(int left_speed, int right_speed);
    void spin_block(int speed, int degrees); // Blocking. Speed: mm/sec, -500 to 500
    void halt(); // Stops both motors. Does not work if used after blocking func
                 // and blocking function has not completed.

    // Sensors

    // Bumper sensor are binary values

    int get_left_bump(); // Left bumper
    int get_right_bump(); // Right bumper

    // Cliff sensor are a range of values; lower values indicates less light,
    // greater values indicates more light.

    int get_center_left_cliff(); // Center left cliff/color sensor
    int get_far_left_cliff(); // Far left cliff/color sensor

    int get_center_right_cliff(); // Center right cliff/color sensor
    int get_far_right_cliff(); // Far right cliff/color sensor

    void line_up_with_black_line(int speed);
    void line_up_with_black_line(int speed, bool debug);

    void center_cliff_line_up_with_black_line(int speed);

    // Wheel encoder distances
    // Try to reset distances frequently
    
    int get_distance();
    void set_distance(int distance);

    // Custom arm functions
    // All functions block until target position is reached.

    // Cup arm
    void cup_arm_right();
    void cup_arm_forward();
    void cup_arm_retract();
    void arm_retract(int c);
    void cup_arm_shake();

    void slow_cup_arm_retract();
    void slow_cup_arm_forward();

    void open_cup_gate();
    void close_cup_gate();
    void shake_cup_gate();

    // Switch arm
    void extend_switch_arm();
    void retract_switch_arm();
    void flick_switch();

    void reset_servos();
};