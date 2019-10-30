/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       dalenash                                                  */
/*    Created:      Wed Oct 30 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftIntake           motor         1               
// RightIntake          motor         2               
// Controller1          controller                    
// LeftDrive1           motor         3               
// LeftDrive2           motor         4               
// LeftDrive3           motor         5               
// LeftDrive4           motor         6               
// RightDrive1          motor         7               
// RightDrive2          motor         8               
// RightDrive3          motor         9               
// RightDrive4          motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

void rollers(int speed) {
    /**
     * Moves both roller motors. Speed will depend on the speed
     * parameter. The range is -100 to 100.
    */
    LeftIntake.spin(directionType::fwd, speed, velocityUnits::pct);
    RightIntake.spin(directionType::rev, speed, velocityUnits::pct);
}

void manipulator(controller::button inBtn, controller::button outBtn) {
    /** 
     * Moves the rollers depending on the state of the up and
     * down buttons. If the up button is pressed, the manipulator
     * will intake, and if the down button is pressed, the manipulator
     * will outtake. The up button has priority.
     */
    if (inBtn.pressing()) {
        rollers(100);
    } else if (outBtn.pressing()) {
        rollers(-100);
    } else {
        rollers(0);
    }
}


/* ----------------------------------------- */
/*   DON'T RUN WITHOUT CHECKING DIRECTIONS   */
/* ----------------------------------------- */
void drive(controller::axis axis3, controller::axis axis1) {
    /** 
     * 
     */


    int difference = axis3.value() - axis1.value();
    int addition = axis3.value() - axis3.value();

    RightDrive1.spin(directionType::fwd, difference, percentUnits::pct);
    RightDrive2.spin(directionType::fwd, difference, percentUnits::pct);
    RightDrive3.spin(directionType::fwd, difference, percentUnits::pct);
    RightDrive4.spin(directionType::fwd, difference, percentUnits::pct);
    LeftDrive1.spin(directionType::fwd, addition, percentUnits::pct);
    LeftDrive2.spin(directionType::fwd, addition, percentUnits::pct);
    LeftDrive3.spin(directionType::fwd, addition, percentUnits::pct);
    LeftDrive4.spin(directionType::fwd, addition, percentUnits::pct);
}



void usercontrol(void) {
    while(1) {
        controller::button INTAKE_IN = Controller1.ButtonUp;
        controller::button INTAKE_OUT = Controller1.ButtonDown;

        controller::axis AXIS3 = Controller1.Axis3;
        controller::axis AXIS1 = Controller1.Axis1;

        drive(AXIS3, AXIS1);

        manipulator(INTAKE_IN, INTAKE_OUT);

        wait(20, msec);
    }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    Competition.drivercontrol(usercontrol);

    while(1) {
        wait(100, msec);
    }

}