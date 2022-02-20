#include "main.h"

// Helper Functions

void SetDrive(int left, int right);

// Driver Control Functions

void TransmissionControl();

void SetDriveMotors();

void SetTiltMotors();

void SetClampPos();

void SetLift();

void SetLiftMotors();

// Autonomous Control Functions

void ResetPosition();

void GetAveragePosition();

void ClampSettings();

void DrivePID(int target);

void Turn(int angle);

void AverageHeading();

void Intake();
// Testing Functions

void Odometry();

void TestOdometry();

void VisionSensorTesting();
