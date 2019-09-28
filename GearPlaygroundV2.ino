/* Gear Playground V2
 *  Erik Nauman and Eryn Gautier
 */

#include <Wire.h>
#include <EVShield.h>
#include <EVs_NXTTouch.h>


// setup for this example:
// attach external power to EVShield.
// attach a touch sensor to BBS1
// attach motors to motor ports (any number of motors is fine).
// Open the Serial terminal to view.

//
// declare the EVShield(s) attached to your Arduino.
//
EVShield    evshield(0x34, 0x36);

//
// declare analog devices attached to evshields.
//
EVs_NXTTouch    touch1, touch2, touch3, touch4;

bool running1, running2, running3, running4;
boolean runningArray[] = {running1, running2, running3, running4};
//
bool touch_status1, touch_status2, touch_status3, touch_status4;
//boolean touchArray[] = {touch_status1, touch_status2, touch_status3, touch_status4};
int motorSpeed = 18;
void setup()
{

  // EVShield provides multiple protocols
  // Initialize the protocol for EVShield
  // It is best to use Hardware I2C (unless you want to use Ultrasonic).
  //
  //evshield.init( SH_SoftwareI2C );
  evshield.init(); // the default is SH_HardwareI2C

  //
  // Initialize the i2c sensors.
  //

  // initialize the analog sensors.
  touch1.init( &evshield, SH_BAS1 );
  touch2.init( &evshield, SH_BAS2 );
  touch3.init( &evshield, SH_BBS1 );
  touch4.init( &evshield, SH_BBS2 );

  //
  // reset motors.
  //
  evshield.bank_a.motorReset();
  evshield.bank_b.motorReset();

  Serial.begin(9600);

}


void loop()
{
//  bool touch_status1, touch_status2, touch_status3, touch_status4;
    touch_status1 = touch1.isPressed();
    touch_status2 = touch2.isPressed();
    touch_status3 = touch3.isPressed();
    touch_status4 = touch4.isPressed();

  boolean touchArray[] = {touch_status1, touch_status2, touch_status3, touch_status4};
//  boolean runningArray[] = {running1, running2, running3, running4};

  //
  //  run the motor if touch sensor is pressed.
  //

  for (int i = 0; i < sizeof(touchArray) / sizeof(boolean); i++) {

    if ( touchArray[i] ) {
      if (!runningArray[i]) {
        switch (i) {
          case 0:
            evshield.bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, motorSpeed);
            break;
          case 1:
            evshield.bank_a.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward, motorSpeed);
            break;
          case 2:
            evshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, motorSpeed);
            break;
          case 3:
            evshield.bank_b.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward, motorSpeed);
            break;
        }

      } else {
        switch (i) {
          case 0:
            evshield.bank_a.motorStop(SH_Motor_1, SH_Next_Action_Brake);
            //running1 = false;
            break;
          case 1:
            evshield.bank_a.motorStop(SH_Motor_2, SH_Next_Action_Brake);
            break;
          case 2:
            evshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);
            break;
          case 3:
            evshield.bank_b.motorStop(SH_Motor_2, SH_Next_Action_Brake);
            break;
        }

      }
      runningArray[i] = !runningArray[i];
      delay (500);
    }
//    Serial.println(runningArray[0]);
  }

}
