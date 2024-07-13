#include "Roomba.h"
#include <iostream>

Roomba::Roomba()
{
    int is_connect_fail = create_connect();

    if (is_connect_fail)
    {
        std::cout << "Failed to connect to Roomba, return code " + std::to_string(is_connect_fail) + "\n";
        throw is_connect_fail;
    }

    create_full();
    enable_servos();
}

// Movement

void Roomba::move_straight(int speed)
{
    create_drive_straight(speed);
}

void Roomba::spin_block(int speed, int degrees)
{
    create_spin_block(speed, degrees);
}

void Roomba::halt()
{
    create_drive_direct(0, 0);
}

// Sensors

// Bumper sensors

int Roomba::get_left_bump()
{
    return get_create_lbump();
}

int Roomba::get_right_bump()
{
    return get_create_rbump();
}

// Cliff sensors

int Roomba::get_center_left_cliff()
{
    return get_create_lfcliff_amt();
}

int Roomba::get_far_left_cliff()
{
    return get_create_lcliff_amt();
}

int Roomba::get_center_right_cliff()
{
    return get_create_rfcliff_amt();
}

int Roomba::get_far_right_cliff()
{
    return get_create_rcliff_amt();
}


// Cup arm


void Roomba::extend_cup_arm()
{
    set_servo_position(CUP_ARM_PIN, CUP_ARM_EXTEND_POS);

    while (get_servo_position(CUP_ARM_PIN) != CUP_ARM_EXTEND_POS)
    {
        msleep(1);
    }
}

void Roomba::retract_cup_arm()
{
    set_servo_position(CUP_ARM_PIN, CUP_ARM_RETRACT_POS);

    while (get_servo_position(CUP_ARM_PIN) != CUP_ARM_RETRACT_POS)
    {
        msleep(1);
    }
}

void Roomba::open_cup_gate()
{
    set_servo_position(CUP_GATE_PIN, CUP_GATE_OPEN_POS);

    while (get_servo_position(CUP_GATE_PIN) != CUP_GATE_OPEN_POS)
    {
        msleep(1);
    }
}

void Roomba::close_cup_gate()
{
    set_servo_position(CUP_GATE_PIN, CUP_GATE_CLOSE_POS);

    while (get_servo_position(CUP_GATE_PIN) != CUP_GATE_CLOSE_POS)
    {
        msleep(1);
    }
}


// Switch arm


void Roomba::extend_switch_arm()
{
    set_servo_position(SWITCH_ARM_PIN, SWITCH_ARM_EXTEND_POS);

    while (get_servo_position(SWITCH_ARM_PIN) != SWITCH_ARM_EXTEND_POS)
    {
        msleep(1);
    }
}

void Roomba::retract_switch_arm()
{
    set_servo_position(SWITCH_ARM_PIN, SWITCH_ARM_RETRACT_POS);

    while (get_servo_position(SWITCH_ARM_PIN) != SWITCH_ARM_RETRACT_POS)
    {
        msleep(1);
    }
}

void Roomba::flick_switch()
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