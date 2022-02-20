// Import Libraries

#include "main.h"

// Motors

pros::Motor LeftLift(6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor RightLift(13, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);


pros::Motor DriveFrontLeft(4, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor DriveBackLeft(3, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor DriveFrontRight(13, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor DriveBackRight(1, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);


pros::Motor TransmissionLeft(5, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor TransmissionRight(12, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);

// Sensors


pros::Imu imu_sensor(9);
pros::Imu imu_sensor2(20);
// Pneumatics

pros::ADIDigitalOut TransmissionPiston('g');
pros::ADIDigitalOut Tilter('h');
pros::ADIDigitalOut Clamp('b');


// Controller

pros::Controller controller(pros::E_CONTROLLER_MASTER);
