/*
 Example sketch for the Xbox Wireless Reciver library - developed by Kristian Lauszus
 It supports up to four controllers wirelessly
 For more information see the blog post: http://blog.tkjelectronics.dk/2012/12/xbox-360-receiver-added-to-the-usb-host-library/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */
 
 //NEW CODE EDIT FOR CHRIS. I PROBABLY WILL NOT BE HERE ON WENDSDAY. ILL LEAVE THIS LAST CODE.. EHEH

#include <XBOXRECV.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
XBOXRECV Xbox(&Usb);

const int
PWM_A   = 3,
DIR_A   = 12,
BRAKE_A = 9,
PWM_B   = 11,
DIR_B   = 13,
BRAKE_B = 8,
SNS_A   = A0,
SNS_B   = A1;

int pos = 0;
int pos2 = 0;
int i = 0;
int r = 0;
int l = 0;
int a = 0;
int b = 0;
int c = 0;
int posX1=0;
int posY1=0;
int posX2=0;
int posY2=0;
int maxSpd=0;
int cir=0;
int arcLengthY=0;
int arcLengthX=0;
//int w = 0;
//int v = 0;

/*#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 
// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(3);*/

void setup() {
  Serial.begin(115200);
    //Serial.begin(9600);           // set up Serial library at 9600 bps
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

   // Configure the A output
  pinMode(BRAKE_A, OUTPUT);  // Brake pin on channel A
  pinMode(DIR_A, OUTPUT);    // Direction pin on channel A
  pinMode(BRAKE_B, OUTPUT);  // Brake pin on channel B
  pinMode(DIR_B, OUTPUT);    // Direction pin on channel B

  
  /*AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);*/
}

void loop() {
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
   // for (uint8_t i = 0; i < 4; i++) {
      i=0;
      if (Xbox.Xbox360Connected[i]) {
        if (Xbox.getButtonPress(L2, i) || Xbox.getButtonPress(R2, i)) {
          Serial.print("L2: ");
          Serial.print(Xbox.getButtonPress(L2, i));
          Serial.print("\tR2: ");
          Serial.println(Xbox.getButtonPress(R2, i));
          Xbox.setRumbleOn(Xbox.getButtonPress(L2, i), Xbox.getButtonPress(R2, i), i);
        }

        if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500 || Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500 || Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500 || Xbox.getAnalogHat(RightHatY, i) > 7500 || Xbox.getAnalogHat(RightHatY, i) < -7500) {
          if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500) {
            Serial.print(F("LeftHatX: "));
            Serial.print(Xbox.getAnalogHat(LeftHatX, i));
            Serial.print("\t");
          }
          if (Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500) {
            Serial.print(F("LeftHatY: "));
            Serial.print(Xbox.getAnalogHat(LeftHatY, i));
            Serial.print("\t");
          }
          if (Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500) {
            Serial.print(F("RightHatX: "));
            Serial.print(Xbox.getAnalogHat(RightHatX, i));
            Serial.print("\t");
          }
          if (Xbox.getAnalogHat(RightHatY, i) > 7500 || Xbox.getAnalogHat(RightHatY, i) < -7500) {
            Serial.print(F("RightHatY: "));
            Serial.print(Xbox.getAnalogHat(RightHatY, i));
          }
          Serial.println();
        }


        pos = map(Xbox.getAnalogHat(LeftHatX, i), -32768, 32767, -255, 255);
        pos2 = map(Xbox.getAnalogHat(LeftHatY, i), -32768, 32767, -255, 255);
        
        if(pos>0){
          digitalWrite(DIR_A, HIGH);   // setting direction to HIGH the motor will spin forward
          digitalWrite(DIR_B, LOW);   // setting direction to HIGH the motor will spin forward
        }
                if(pos<0){
          digitalWrite(DIR_A, LOW);   // setting direction to HIGH the motor will spin forward
          digitalWrite(DIR_B, HIGH);   // setting direction to HIGH the motor will spin forward
        }
        
        //Serial.print("pos: "+pos);
        //Serial.println("pos2: "+pos2);
        
       // pos = 1/pos;

       /* v = (256-abs(pos)) * (pos2/256) + pos2;
        w = (256-abs(pos2)) * (pos/256) + pos;
        r = (v+w)/2;
        l = (v-w)/2;*/

        Serial.print("Speed: ");
        Serial.print(pos);
        Serial.print(" and ");
        Serial.print(pos);
        if(pos>0){
        Serial.println("\nDirection: Forward");
        }
        else{
          Serial.println("\nDirection: Backward");
        }
        //mathew's code
        /*

        a = Xbox.getAnalogHat(LeftHatX, i);
        b = Xbox.getAnalogHat(LeftHatY, i);
        c = (int) (sqrt(pow(a, 2) + pow(b, 2)));
        Serial.print("Speed: ");
        Serial.println(c/128);
        
        r=round(c/128);
        l=round(b/128);

        //Must Fix Down-Right and Up-Left

          if (a > 4095){                             //Stick is pointed right
            if (b > 4095){
              digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, HIGH);
              digitalWrite(DIR_B, LOW);
              analogWrite(PWM_A, r); 
              analogWrite(PWM_B, l);
            }
            else if (b < -4096){
              digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, LOW);
              digitalWrite(DIR_B, HIGH);
              analogWrite(PWM_A, r); 
              analogWrite(PWM_B, l);
            }
            else{                                   //Tank turn Right
              digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, LOW);
              digitalWrite(DIR_B, LOW);
              analogWrite(PWM_A, round(a/128)); 
              analogWrite(PWM_B, round(a/128));
            }
          }
          else if (a < -4096){                      //Stick is pointed left
            if (b > 4095){
              digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, HIGH);
              digitalWrite(DIR_B, LOW);
              analogWrite(PWM_A, r); 
              analogWrite(PWM_B, l);
            }
            else if (b < -4096){
              digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, LOW);
              digitalWrite(DIR_B, HIGH);
              analogWrite(PWM_A, r); 
              analogWrite(PWM_B, l);
            }
            else{                                   //Tank turn Left
              digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, HIGH);
              digitalWrite(DIR_B, HIGH);
              analogWrite(PWM_A, round(a/128)); 
              analogWrite(PWM_B, round(a/128));
            }
          }
          else{                                   //Stick pointed Up, Forwards
            if(b > 4095){
              digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, HIGH);
              digitalWrite(DIR_B, LOW);
              analogWrite(PWM_A, round(b/128)); 
              analogWrite(PWM_B, round(b/128));
            }
            else if(b < -4096){                           //Stick pointed Down, Backwards
              digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, LOW);
              digitalWrite(DIR_B, HIGH);
              analogWrite(PWM_A, round(b/128)); 
              analogWrite(PWM_B, round(b/128));
            }
            else{                              //Stick is in the centre, Stop
              digitalWrite(BRAKE_A, HIGH);
              digitalWrite(BRAKE_B, HIGH);
            }
          }
        //end for mathew's code
        */
        
        /*if(b>3000){
          digitalWrite(BRAKE_A, LOW);
          digitalWrite(BRAKE_B, LOW);
          digitalWrite(DIR_A, HIGH);
          digitalWrite(DIR_B, LOW);
        }
        else if(b<-3000){
         digitalWrite(BRAKE_A, LOW);
         digitalWrite(BRAKE_B, LOW);
         digitalWrite(DIR_A, LOW);
         digitalWrite(DIR_B, HIGH);
        }
        else{
        digitalWrite(BRAKE_A, HIGH);
        digitalWrite(BRAKE_B, HIGH);
        }
        
        if(a>=32767-512){
          digitalWrite(DIR_A, LOW);
          digitalWrite(DIR_B, HIGH);
        }
        if(a<=-32768+512){
          digitalWrite(DIR_A, HIGH);
          digitalWrite(DIR_B, LOW);
        }
        if(b>=32767-512){
          digitalWrite(DIR_A, HIGH);
          digitalWrite(DIR_B, LOW);
        }
        if(b<=-32767+512){
          digitalWrite(DIR_A, LOW);
          digitalWrite(DIR_B, HIGH);
        }

        r=(c-a)/128;
        l=(c-b)/128;
        
        analogWrite(PWM_A, r); 
        analogWrite(PWM_B, l);
        */

        //chris code UPDATED JAN 31, 2015 (SOLUTIONS TO OUR TURNING PROBLEM. i think) I never tested this. please fix if nessesary. probaly wont work thouh. i wrote down the theroy
        // if this program does not work, to fix
        //how to fix. find out how to mesures angles for circle and two points.
        //propaby university or grade 11-12 stuff. ask Mathew if he knows. MATHew eheh get it ? ( probably spelt his name wrong though...)
        posX1 = map(Xbox.getAnalogHat(RightHatX, i), -32768, 32767, -255, 255);
        posY1 = map(Xbox.getAnalogHat(RightHatY, i), -32768, 32767, -255, 255);
        maxSpd= sqrt(pow(posX1,2)+pow(posY1,2)); //X2+Y2=R2 for max spd
        //imagin the joystick is divided into 8 pieces.
        /*
        joystick layout
            Y
         \ 1|2 /
        3 \ | /  4
       -----------X
        5 / | \6
         / 7|8 \
        
        */
if (RightHatY>0){//checks if your joystick is up so for #1-4
       if (RightHatX<0){//check for area 1 and 3
            if (abs(posX)<abs(posY)){//check for area 1 
            analogWrite(PWM_A, maxSpd); //right at max speed foward
            analogWrite(PWM_B, maxSpd*abs(posX)/abs(posY));//left scaling speed foward
            }
             if (abs(posX)>abs(posY)){//check for area 3
            analogWrite(PWM_A, maxSpd); //right at max speed foward
            analogWrite(PWM_B, -(maxSpd*abs(posY)/abs(posX)));//left scaling speed backwards
            }
       }//end if for 1 and 3
       if (RightHatX<0){//check for area 2 and 4
            if (abs(posX)<abs(posY)){//check for area 2 
            analogWrite(PWM_A, maxSpd*abs(posX)/abs(posY)); //right at scaling speed foward
            analogWrite(PWM_B, maxSpd);//left max speed foward
            }
             if (abs(posX)>abs(posY)){//check for area 4
            analogWrite(PWM_A, -(maxSpd*abs(posY)/abs(posX))); //right at scaling speed backwards
            analogWrite(PWM_B, maxSpd);//left max speed forwards
            }
       }//end if for 2 and 4
}//end for 1-4
if (RightHatY<0){//checks if your joystick is up so for #5-8
       if (RightHatX<0){//check for area 5 and 7
            if (abs(posX)<abs(posY)){//check for area 7
            analogWrite(PWM_A, -maxSpd); //right at max speed backwards
            analogWrite(PWM_B, -maxSpd*abs(posX)/abs(posY));//left scaling speed backwards
            }
             if (abs(posX)>abs(posY)){//check for area 5
            analogWrite(PWM_A, -maxSpd); //right at max speed back
            analogWrite(PWM_B, (maxSpd*abs(posY)/abs(posX)));//left scaling speed forward
            }
       }//end if for 5 and 7
       if (RightHatX<0){//check for area 6 and 8
            if (abs(posX)<abs(posY)){//check for area 8 
            analogWrite(PWM_A, -maxSpd*abs(posX)/abs(posY)); //right at scaling speed back
            analogWrite(PWM_B, -maxSpd);//left max speed back
            }
             if (abs(posX)>abs(posY)){//check for area 6
            analogWrite(PWM_A, (maxSpd*abs(posY)/abs(posX))); //right at scaling speed forwards
            analogWrite(PWM_B, -maxSpd);//left max speed back
            }
       }//end if for 6 and 8
}//end for 5-8

//ENDEND END END END 

  /*
        int x_axis = AnalogRead(0); // value of X-Axis joystick (0-1023, 512 = centered)
  int y_axis = AnalogRead(1); // value of Y-Axis joystick (0-1023, 512 = centered)

  // filter out a centered joystick - no action
  if (x_axis < 510 || x_axis > 514) {
    if (y_axis < 510 || y_axis > 514) {
      // Map values from potentiometers to a smaller range for the PWM motor controllers (0-255)
      x_axis = map(x_axis, 0, 1023, 0, 255);
      y_axis = map(y_axis, 0, 1023, 0, 255);

      int ly_axis = y_axis;
      int ry_axis = y_axis;

      if (x_axis < 126) { // turning left, so slow-down left track
        if (y_axis > 130) { // moving forward
          ly_axis -= (255 - x_axis); // decreasing the value - moving it closer to the center-point - slows it down
        }

        if (y_axis < 126) { // moving in reverse
          ly_axis += (255 - x_axis); // increasing the value - moving it closer to the center-point - slows it down
        }
      }

      if (x_axis > 130) { // turning right, so slow-down right track
        if (y_axis > 130) { // moving forward
          ry_axis -= (255 - x_axis); // decreasing the value - moving it closer to the center-point - slows it down
        }

        if (y_axis < 126) { // moving in reverse
          ry_axis += (255 - x_axis); // increasing the value - moving it closer to the center-point - slows it down
        }
      }

      l_track.write(ly_axis); // here we assume that values > 128 = forward, and < 128 = reverse for the left track motor controller
      r_track.write(ry_axis); // here we assume that values > 128 = forward, and < 128 = reverse for the right track motor controller
    }
  }

  // center both PWM values if the joystick is centered (bringing both motor controllers and tracks to a stop)
  if (x_axis >= 510 || x_axis <= 514) {
    if (y_axis >= 510 || y_axis <= 514) {
      l_track.write(128);
      r_track.write(128);
 
         */
        //end
        /*if(r==l){
          digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
            digitalWrite(DIR_A, HIGH);   // setting direction to HIGH the motor will spin forward
            analogWrite(PWM_A, r); 
            analogWrite(PWM_B, l); 
        }*/
        
        
        
        /*if (r>0){
            digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
            digitalWrite(DIR_A, HIGH);   // setting direction to HIGH the motor will spin forward
            analogWrite(PWM_A, r); 
          
        }
        else if (r<0){
           digitalWrite(BRAKE_A, LOW);  // setting againg the brake LOW to disable motor brake
           digitalWrite(DIR_A, LOW);    // now change the direction to backward setting LOW the DIR_A pin
           analogWrite(PWM_A, r);     // Set the speed of the motor
        }
        else {
           digitalWrite(BRAKE_A, HIGH);
        }
         if (l>0){
          digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
          digitalWrite(DIR_B, LOW);   // setting direction to HIGH the motor will spin forward
          analogWrite(PWM_B, l);
        }
        else if (l<0){
          digitalWrite(BRAKE_B, LOW);  // setting againg the brake LOW to disable motor brake
          digitalWrite(DIR_B, HIGH);    // now change the direction to backward setting LOW the DIR_A pin
          analogWrite(PWM_B, l);     // Set the speed of the motor
        }
        else {
          digitalWrite(BRAKE_A, HIGH);
        }
     /*   
         if (Xbox.getAnalogHat(LeftHatX, i) < 32639){
            if (Xbox.getAnalogHat(LeftHatX, i) > -32640){
              if (Xbox.getAnalogHat(LeftHatY, i) < 2047 && Xbox.getAnalogHat(LeftHatY, i) > -2048/* || Xbox.getAnalogHat(LeftHatX, i) < 2047 && Xbox.getAnalogHat(LeftHatX, i) > -2048*/ /*){
     /*           myMotor->run(RELEASE);
              myOtherMotor->run(RELEASE);
              }
           }
         }
*/
       //  if (Xbox.getAnalogHat(LeftHatY, i) >= 2047 /*|| Xbox.getAnalogHat(LeftHatY, i) < 0*/ /*){ */
        // pos = map(Xbox.getAnalogHat(LeftHatY, i), /*-32768*/ /*-32768*/0, 32767, /*-256*/ 0, 255);
         /* Serial.print(F("pos: "));
          Serial.println(pos);
                myMotor->setSpeed(pos);
                myOtherMotor->setSpeed(pos);
                delay(10);
                myMotor->run(FORWARD);
              myOtherMotor->run(FORWARD);
         }
         if (Xbox.getAnalogHat(LeftHatY, i) <= -2048){
         pos = map(Xbox.getAnalogHat(LeftHatY, i), 0, -32768, 0, 255);
          Serial.print(F("pos: "));
          Serial.println(pos);
                myMotor->setSpeed(pos);
                myOtherMotor->setSpeed(pos);
                delay(10);
                myMotor->run(BACKWARD);
              myOtherMotor->run(BACKWARD);
         }
         
         if (Xbox.getAnalogHat(LeftHatX, i) > 2048 && Xbox.getAnalogHat(LeftHatY, i) > -2048 && Xbox.getAnalogHat(LeftHatY, i) < 2047){
         pos2 = map(Xbox.getAnalogHat(LeftHatX, i), 0, 32767, 0, 255);
          Serial.print(F("pos: "));
          Serial.println(pos);
                myMotor->setSpeed(pos2);
                myOtherMotor->setSpeed(pos2);
                delay(10);
                myMotor->run(BACKWARD);
              myOtherMotor->run(FORWARD);
         }
         
         if (Xbox.getAnalogHat(LeftHatX, i) < -2048 && Xbox.getAnalogHat(LeftHatY, i) > -2048 && Xbox.getAnalogHat(LeftHatY, i) < 2047){
         pos2 = map(Xbox.getAnalogHat(LeftHatX, i), 0, 32767, 0, 255);
          Serial.print(F("pos: "));
          Serial.println(pos);
                myMotor->setSpeed(pos2);
                myOtherMotor->setSpeed(pos2);
                delay(10);
                myMotor->run(FORWARD);
              myOtherMotor->run(BACKWARD);
         }
         if (Xbox.getAnalogHat(LeftHatX, i) > 2047 && Xbox.getAnalogHat(LeftHatY, i) <= -2048 && Xbox.getAnalogHat(LeftHatY, i) >= 2047){
         pos2 = map(Xbox.getAnalogHat(LeftHatX, i), 0, 32767, 0, 255);
          Serial.print(F("pos: "));
          Serial.println(pos);
                myMotor->setSpeed(pos);
                myOtherMotor->setSpeed(pos2);
                delay(10);
                myMotor->run(FORWARD);
              myOtherMotor->run(FORWARD);
         }
         if (Xbox.getAnalogHat(LeftHatX, i) < -2048 && Xbox.getAnalogHat(LeftHatY, i) <= -2048 && Xbox.getAnalogHat(LeftHatY, i) >= 2047){
         pos2 = map(Xbox.getAnalogHat(LeftHatX, i), 0, -32768, 0, 255);
          Serial.print(F("pos: "));
          Serial.println(pos);
                myMotor->setSpeed(pos2);
                myOtherMotor->setSpeed(pos);
                delay(10);
                myMotor->run(FORWARD);
              myOtherMotor->run(FORWARD);
         }
*/

        if (Xbox.getButtonClick(UP, i)) {
          Xbox.setLedOn(LED1, i);
          Serial.println(F("Up"));
          digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
          digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
          digitalWrite(DIR_A, HIGH);
          digitalWrite(DIR_B, LOW);
          analogWrite(PWM_A, 200); 
          analogWrite(PWM_B, 200);    
        }
        if (Xbox.getButtonClick(DOWN, i)) {
          Xbox.setLedOn(LED4, i);
          Serial.println(F("Down"));
          digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
          digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
          digitalWrite(DIR_A, LOW);
          digitalWrite(DIR_B, HIGH); 
          analogWrite(PWM_A, 200); 
          analogWrite(PWM_B, 200);    
        }
        if (Xbox.getButtonClick(LEFT, i)) {
          Xbox.setLedOn(LED3, i);
          digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
          digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
          Serial.println(F("Left"));
          digitalWrite(DIR_A, HIGH);
          digitalWrite(DIR_B, HIGH); 
          analogWrite(PWM_A, 200); 
          analogWrite(PWM_B, 200);    
        }
        if (Xbox.getButtonClick(RIGHT, i)) {
          Xbox.setLedOn(LED2, i);
          Serial.println(F("Right"));
          digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
          digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
          digitalWrite(DIR_A, LOW);
          digitalWrite(DIR_B, LOW);
          analogWrite(PWM_A, 200); 
          analogWrite(PWM_B, 200);    
        }

        if (Xbox.getButtonClick(START, i)) {
          Xbox.setLedMode(ALTERNATING, i);
          Serial.println(F("Start"));
        }
        if (Xbox.getButtonClick(BACK, i)) {
          Xbox.setLedBlink(ALL, i);
          Serial.println(F("Back"));
        }
        if (Xbox.getButtonClick(L3, i))
        {
          Serial.println(F("L3"));
            digitalWrite(BRAKE_A, HIGH);
            digitalWrite(BRAKE_B, HIGH);}
        if (Xbox.getButtonClick(R3, i))
          Serial.println(F("R3"));

        if (Xbox.getButtonClick(L1, i))
          Serial.println(F("L1"));
        if (Xbox.getButtonClick(R1, i))
          Serial.println(F("R1"));
        if (Xbox.getButtonClick(XBOX, i)) {
          Xbox.setLedMode(ROTATING, i);
          Serial.print(F("Xbox (Battery: "));
          Serial.print(Xbox.getBatteryLevel(i)); // The battery level in the range 0-3
          Serial.println(F(")"));
        }
        if (Xbox.getButtonClick(SYNC, i)) {
          Serial.println(F("Sync"));
          Xbox.disconnect(i);
        }

        if (Xbox.getButtonClick(A, i))
          Serial.println(F("A"));
        if (Xbox.getButtonClick(B, i)){
          Serial.println(F("B"));
              digitalWrite(BRAKE_A, HIGH);;
              digitalWrite(BRAKE_B, HIGH);}
        if (Xbox.getButtonClick(X, i))
          Serial.println(F("X"));
        if (Xbox.getButtonClick(Y, i))
          Serial.println(F("Y"));
      }
  //  }
  }
}
