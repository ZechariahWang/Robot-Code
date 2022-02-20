// MAIN CPP FILE FOR ROBOT CONTROL (Driver control, autonomous, etc)


///////////////////////////////////////////////////
////////////////Import Libraries///////////////////
///////////////////////////////////////////////////

#include "main.h"
#include "math.h"
#include <cmath>
#include "iostream"

#define public


///////////////////////////////////////////////////
/////////////////Global Variables//////////////////
///////////////////////////////////////////////////

double x;
double y;
double h;

bool transmissionvalue = false;
bool Switch = false;
bool value = false;
bool ClampPos = false;


int TransmissionDelay = 50;
int TilterDelay = 100;



/////////////////////////////////////////////////////////////
/////////////////Driver Control Functions////////////////////
/////////////////////////////////////////////////////////////



///////////////////////////////////////////////////
///////////////Set Drive Function//////////////////
///////////////////////////////////////////////////

void SetDrive(int left, int right){

  DriveFrontLeft.move_voltage(left);
//  DriveBackLeft.move_voltage(left);
  DriveFrontRight.move_voltage(right);
//  DriveBackRight.move_voltage(right);

  if (Switch){

//    TransmissionLeft.move_voltage(left);

//    TransmissionRight.move_voltage(right);

  }

}

///////////////////////////////////////////////////
/////////Primary Driver Control Function///////////
///////////////////////////////////////////////////

void SetDriveMotors(){

  int leftYjoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

  int leftXjoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

  int rightYjoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

  int rightXjoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

  if(abs(leftYjoystick) < 10){

      leftYjoystick = 0;

  }

  if(abs(rightYjoystick) < 10){

      rightYjoystick = 0;

  }

  SetDrive((rightXjoystick + leftYjoystick) * 80, (leftYjoystick - rightXjoystick) * 80);

}

///////////////////////////////////////////////////
///////////Transmission Control Function///////////
///////////////////////////////////////////////////

bool bindtransmission = false;


void TransmissionControl(){

    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
        bindtransmission = !bindtransmission;
    }

    if(bindtransmission){
      Switch = false;
      TransmissionPiston.set_value(true);
      chassis.pto_toggle({TransmissionLeft, TransmissionRight}, true);
      pros::delay(TransmissionDelay);
    }
    else{

      TransmissionPiston.set_value(false);
      Switch = true;
      chassis.pto_toggle({TransmissionLeft, TransmissionRight}, false);
      pros::delay(TransmissionDelay);

    }

}

//94.4881889764

///////////////////////////////////////////////////
////////////Tilter Control Function////////////////
///////////////////////////////////////////////////

bool tiltkey = false;

void SetTiltMotors(){

  if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
      tiltkey = !tiltkey;
  }

  if(tiltkey){
    Tilter.set_value(true);
    pros::delay(TilterDelay);

  }

  else{
    Tilter.set_value(false);

  }

  pros::delay(10);

}

///////////////////////////////////////////////////
/////////////Clamp Control Function////////////////
///////////////////////////////////////////////////

bool status = false;

void SetClampPos(){

  if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
      status = !status;
  }

  if(status){
    Clamp.set_value(true);

  }

  else{
    Clamp.set_value(false);
  }

  pros::delay(10);

}

///////////////////////////////////////////////////
/////////////Lift Control Function/////////////////
///////////////////////////////////////////////////

int liftvalue = 500;

void SetLift(int power){

  LeftLift.move_voltage(power);
  RightLift.move_voltage(power);

}

void SetLiftMotors(){

  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
    int liftpower = 11000;
    SetLift(liftpower);

    pros::delay(10);

  }

  else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
    int liftpower = -11000;
    SetLift(liftpower);

    pros::delay(10);

  }

  else{
    int liftpower = 0;
    SetLift(liftpower);
  }

}
