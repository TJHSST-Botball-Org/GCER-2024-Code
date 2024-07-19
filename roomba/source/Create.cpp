#include "Create.h"
#include <iostream>

Create::Create()
{
    int is_connect_fail = create_connect();

    if (is_connect_fail)
    {
        std::cout << "Failed to connect to Create, return code " + std::to_string(is_connect_fail) + "\n";
        throw is_connect_fail;
    }

    create_full();
    enable_servos();

    this->set_distance(0);
}

Create::~Create()
{
    disable_servos();
    create_disconnect();
}

// Movement

void Create::move_straight(int speed)
{
    create_drive_straight(speed);
}

void Create::drive_direct(int left_speed, int right_speed)
{
    create_drive_direct(left_speed, right_speed);
}

void Create::spin_block(int speed, int degrees)
{
    create_spin_block(speed, degrees);
}

void Create::halt()
{
    create_drive_direct(0, 0);
}

// Sensors

// Bumper sensors

int Create::get_left_bump()
{
    return get_create_lbump();
}

int Create::get_right_bump()
{
    return get_create_rbump();
}

// Cliff sensors

int Create::get_center_left_cliff()
{
    return get_create_lfcliff_amt();
}

int Create::get_far_left_cliff()
{
    return get_create_lcliff_amt();
}

int Create::get_center_right_cliff()
{
    return get_create_rfcliff_amt();
}

int Create::get_far_right_cliff()
{
    return get_create_rcliff_amt();
}

// Wheel encoder distances

int Create::get_distance()
{
    return get_create_distance();
}

void Create::set_distance(int distance)
{
    set_create_distance(distance);
}


// Cup arm

void Create::cup_arm_right()
{
    set_servo_position(CUP_ARM_PIN, CUP_ARM_RIGHT_POS);

    while (get_servo_position(CUP_ARM_PIN) != CUP_ARM_RIGHT_POS)
    {
        msleep(1);
    }
}

void Create::cup_arm_forward()
{
    set_servo_position(CUP_ARM_PIN, CUP_ARM_FORWARD_POS);

    while (get_servo_position(CUP_ARM_PIN) != CUP_ARM_FORWARD_POS)
    {
        msleep(1);
    }
}

void Create::cup_arm_retract()
{
    set_servo_position(CUP_ARM_PIN, CUP_ARM_RETRACT_POS);

    while (get_servo_position(CUP_ARM_PIN) != CUP_ARM_RETRACT_POS)
    {
        msleep(1);
    }
}

void Create::open_cup_gate()
{
    set_servo_position(CUP_GATE_PIN, CUP_GATE_OPEN_POS);

    while (get_servo_position(CUP_GATE_PIN) != CUP_GATE_OPEN_POS)
    {
        msleep(1);
    }
}

void Create::close_cup_gate()
{
    set_servo_position(CUP_GATE_PIN, CUP_GATE_CLOSE_POS);

    while (get_servo_position(CUP_GATE_PIN) != CUP_GATE_CLOSE_POS)
    {
        msleep(1);
    }
}


// Switch arm


void Create::extend_switch_arm()
{
    set_servo_position(SWITCH_ARM_PIN, SWITCH_ARM_EXTEND_POS);

    while (get_servo_position(SWITCH_ARM_PIN) != SWITCH_ARM_EXTEND_POS)
    {
        msleep(1);
    }
}

void Create::retract_switch_arm()
{
    set_servo_position(SWITCH_ARM_PIN, SWITCH_ARM_RETRACT_POS);

    while (get_servo_position(SWITCH_ARM_PIN) != SWITCH_ARM_RETRACT_POS)
    {
        msleep(1);
    }
}

void Create::flick_switch()
{
    this->extend_switch_arm();
    
    set_servo_position(SWITCH_ARM_PIN, SWITCH_ARM_ABOVE_SWITCH_POS);
    while (get_servo_position(SWITCH_ARM_PIN) != SWITCH_ARM_ABOVE_SWITCH_POS)
    {
        msleep(1);
    }

    this->extend_switch_arm();

    set_servo_position(SWITCH_ARM_PIN, SWITCH_ARM_ABOVE_SWITCH_POS);
    while (get_servo_position(SWITCH_ARM_PIN) != SWITCH_ARM_ABOVE_SWITCH_POS)
    {
        msleep(1);
    }
}

void Create::reset_servos()
{
    this->cup_arm_retract();
    this->retract_switch_arm();
    this->close_cup_gate();
}