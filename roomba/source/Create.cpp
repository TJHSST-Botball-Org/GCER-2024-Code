#include "Create.h"
#include <iostream>
#include <string>

Create::Create()
{
    int is_connect_fail = create_connect();

    if (is_connect_fail)
    {
        std::cout << "Failed to connect to Create, return code " + std::to_string(is_connect_fail) + "\n";
        throw is_connect_fail;
    }

    this->cup_arm_retract();
    this->retract_switch_arm();
    this->close_cup_gate();

    create_full();
    enable_servos();

    this->set_distance(0);
}

Create::~Create()
{
    std::cout << "Create destructor called\n" << std::flush;
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

// Moves until black line, and then lines up.
void Create::line_up_with_black_line(int speed)
{
    this->line_up_with_black_line(speed, false);
}

void Create::line_up_with_black_line(int speed, bool debug)
{
    while (!(this->get_far_left_cliff() < Create::CLIFF_SENSOR_THRESHOLD && this->get_far_right_cliff() < Create::CLIFF_SENSOR_THRESHOLD))
    {
        // While not both sensors aligned

        if (this->get_far_left_cliff() > Create::CLIFF_SENSOR_THRESHOLD && this->get_far_right_cliff() > Create::CLIFF_SENSOR_THRESHOLD)
        {
            // Both sensors not sensing color
            this->move_straight(speed);
        }
        else if (this->get_far_left_cliff() < Create::CLIFF_SENSOR_THRESHOLD)
        {
            // Left side ahead
            this->drive_direct(0, speed);
        }
        else
        {
            // Right side ahead
            this->drive_direct(speed, 0);
        }
        if (debug)
        {
            std::cout << "Liningup " + std::to_string(this->get_far_left_cliff()) + " " + std::to_string(this->get_far_right_cliff()) + "\n" << std::flush;
        }
        msleep(1);
    }   

}

void Create::center_cliff_line_up_with_black_line(int speed)
{
    while (!(this->get_center_left_cliff() < Create::CLIFF_SENSOR_THRESHOLD && this->get_center_right_cliff() < Create::CLIFF_SENSOR_THRESHOLD))
    {
        // While not both sensors aligned

        if (this->get_center_left_cliff() > Create::CLIFF_SENSOR_THRESHOLD && this->get_center_right_cliff() > Create::CLIFF_SENSOR_THRESHOLD)
        {
            // Both sensors not sensing color
            this->move_straight(speed);
        }
        else if (this->get_center_left_cliff() < Create::CLIFF_SENSOR_THRESHOLD)
        {
            // Left side ahead
            this->drive_direct(0, speed);
        }
        else
        {
            // Right side ahead
            this->drive_direct(speed, 0);
        }
        msleep(1);
    }   

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

void Create::cup_arm_shake()
{
    set_servo_position(CUP_ARM_PIN, CUP_ARM_RIGHT_POS + CUP_ARM_SHAKE_AMOUNT);
    msleep(250);
    set_servo_position(CUP_ARM_PIN, CUP_ARM_RIGHT_POS - CUP_ARM_SHAKE_AMOUNT);
    msleep(250);
    set_servo_position(CUP_ARM_PIN, CUP_ARM_RIGHT_POS + CUP_ARM_SHAKE_AMOUNT);
    msleep(250);
    set_servo_position(CUP_ARM_PIN, CUP_ARM_RIGHT_POS - CUP_ARM_SHAKE_AMOUNT);
    msleep(250);
    set_servo_position(CUP_ARM_PIN, CUP_ARM_RIGHT_POS + CUP_ARM_SHAKE_AMOUNT);
}

void Create::slow_cup_arm_retract()
{
    int curr_servo_pos = get_servo_position(CUP_ARM_PIN);
    while (curr_servo_pos != CUP_ARM_RETRACT_POS)
    {
        if (curr_servo_pos > CUP_ARM_RETRACT_POS)
        {
            curr_servo_pos -= 1;
        }
        else
        {
            curr_servo_pos += 1;
        }

        set_servo_position(CUP_ARM_PIN, curr_servo_pos);

        msleep(10);
    }
    set_servo_position(CUP_ARM_PIN, CUP_ARM_RETRACT_POS);
}

void Create::slow_cup_arm_forward()
{
    int curr_servo_pos = get_servo_position(CUP_ARM_PIN);
    while (curr_servo_pos != CUP_ARM_FORWARD_POS)
    {
        if (curr_servo_pos > CUP_ARM_FORWARD_POS)
        {
            curr_servo_pos -= 1;
        }
        else
        {
            curr_servo_pos += 1;
        }

        set_servo_position(CUP_ARM_PIN, curr_servo_pos);

        msleep(10);
    }
    set_servo_position(CUP_ARM_PIN, CUP_ARM_FORWARD_POS);
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
    
    set_servo_position(SWITCH_ARM_PIN, 1500);
}

void Create::reset_servos()
{
    this->cup_arm_retract();
    this->retract_switch_arm();
    this->close_cup_gate();
}