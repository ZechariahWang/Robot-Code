#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-4}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{13}

  // IMU Port
  ,15

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,4.125

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,200

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.4

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);

void Commands(){

  chassis.set_drive_pid(24, 100, true);
  chassis.wait_drive();
  chassis.set_turn_pid(90, 110);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, 100);

}

void SkillsAuton(){


//    chassis.pto_toggle({TransmissionLeft, TransmissionRight}, true);

  chassis.reset_drive_sensor();
  chassis.set_drive_pid(-5, -110, true);
  chassis.wait_drive();
  std::cout << "Done 1" << std::endl;


  chassis.reset_drive_sensor();
  chassis.set_drive_pid(5, 110, true);
  chassis.wait_drive();
  std::cout << "Done 2" << std::endl;


  chassis.set_turn_pid(90, 110);
  chassis.wait_drive();
  chassis.set_angle(0);
  std::cout << "Done 3" << std::endl;

  chassis.reset_drive_sensor();
  chassis.set_drive_pid(24, 110, true);
  chassis.wait_drive();
  std::cout << "Done 4" << std::endl;

  pros::delay(1000);

  chassis.set_turn_pid(90, 110);
  chassis.wait_drive();
  std::cout << "Done 5" << std::endl;


}



void TempAuton(){

    chassis.pto_toggle({TransmissionLeft, TransmissionRight}, true);

    chassis.set_drive_pid(-5, -110, false, true);

    chassis.wait_drive();

    chassis.set_turn_pid(180, 110);

    chassis.wait_drive();



}

void Testing(){

  chassis.set_turn_pid(90, 90);
  chassis.wait_drive();

  pros::delay(10);

  chassis.set_turn_pid(180, 90);
  chassis.wait_drive();

  pros::delay(10);

  chassis.set_turn_pid(90, 90);
  chassis.wait_drive();



}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
//  ez::print_ez_template();

  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)
  default_constants(); // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used.
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({

    Auton("Programming Skills\n\ntemp 1", SkillsAuton),

    Auton("Temp Auton\n\ntemp 2", TempAuton),

  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();

  chassis.pto_add({TransmissionLeft, TransmissionRight});

  // Motor presets

  DriveFrontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  DriveBackLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  DriveFrontRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  DriveBackRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);


  LeftLift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  RightLift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);


  imu_sensor.reset();
  imu_sensor2.reset();

  imu_sensor.tare_rotation();
  imu_sensor2.tare_rotation();

}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}


/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  ProgrammingSkills();

}



bool pto_intake_enabled = false;

void pto_intake(bool toggle) {
  pto_intake_enabled = toggle;
  chassis.pto_toggle({TransmissionLeft, TransmissionRight}, toggle);
  TransmissionPiston.set_value(toggle);
  if (toggle) {
    TransmissionLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    TransmissionRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  }
}

void set_intake(int input) {
  if (!pto_intake_enabled) return;
  TransmissionLeft = input;
  TransmissionRight = input;
}

void opcontrol() {
  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  while (true) {

  //  chassis.arcade_standard(ez::SPLIT);

    SetDriveMotors();

    TransmissionControl();

    SetClampPos();

    SetTiltMotors();

    SetLiftMotors();
    // Tank control
    // chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
