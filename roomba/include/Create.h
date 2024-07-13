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
    // CREATE SETTINGS HERE

    // Pins
    static const int SWITCH_ARM_PIN = 0;
    static const int CUP_ARM_PIN = 1;
    static const int CUP_GATE_PIN = 2;

    // Servo limits
    static const int CUP_ARM_EXTEND_POS = 0;
    static const int CUP_ARM_RETRACT_POS = 100;

    static const int CUP_GATE_OPEN_POS = 0;
    static const int CUP_GATE_CLOSE_POS = 100;

    static const int SWITCH_ARM_EXTEND_POS = 0;
    static const int SWITCH_ARM_ABOVE_SWITCH_POS = 50;
    static const int SWITCH_ARM_RETRACT_POS = 100;

    // Sensor limits
    static const int CLIFF_SENSOR_THRESHOLD = 500;

public:
    Create();
    ~Create();

    // Movement

    void move_straight(int speed); // Non-blocking. Speed: mm/sec, -500 to 500
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



    // Custom arm functions
    // All functions block until target position is reached.

    // Cup arm
    void extend_cup_arm();
    void retract_cup_arm();
    void open_cup_gate();
    void close_cup_gate();

    // Switch arm
    void extend_switch_arm();
    void retract_switch_arm();
    void flick_switch();
};