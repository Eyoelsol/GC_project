/*
LCD display and the motor speed control using a joystick
*/


#include <Stepper.h>
#include <LiquidCrystal.h>

#define STEPS 20

LiquidCrystal LCD(13,12,6,5,7,4); // creating an instance of the LCD display
Stepper stepper(STEPS, 8, 9, 10, 11); //creating an instance of the Motor

const int Y_axis = A0; // The joystick Y input is connected to A0;
const int X_axis = A1; // The joystick X input is connected to A0;
int Xaxis=0; //initializing analog value of X axis
int Yaxis=0; //initializing analog value of Y axis 
const int button =  3; // direction control button is connected to Arduino pin 4

    void setup()
    {
      
    pinMode(button, INPUT_PULLUP); // configuring button pin as input with internal pull up enabled 
    pinMode(A0,INPUT);//analog input of the X axis
    pinMode(A1,INPUT);//analog input of the y axis
    LCD.begin(16,2); 
    
    }

int direction_ = 1; //initializing thr direction of the motor
int speed_ = 0; //initializing speed
int maxSpeed = 20; // setting the maximum speed

    void loop()
    {
    
    speedMotor();
    displayLCD();
    
    }

//method for display
      void displayLCD(){
      
      Xaxis = analogRead(X_axis); // reading analog value of x axis
      LCD.setCursor(0,1); //setting the lcd cursor on the 2nd row
      
      if(Xaxis>520){
      LCD.print("<-- "); //displaying left direction
      }
      
      else if(Xaxis<502){
      LCD.print("-->  "); //displaying right direction
      }
      
      else{
      LCD.print("    ");//nothing displays when joystick position in the middle
      }


      //desplaying alert message when moving in high speed
      if(speed_ >= 28){
      
      LCD.setCursor(0,0);
      LCD.write("ALERT:HIGH SPEED");
      LCD.setCursor(0,1);
      LCD.write("PUT ON SEAT-BELT");
      }
      
      }

      void speedMotor(){
      
      if ( digitalRead(button) == 0 )  // if button is pressed
      if ( debounce() )  // debounce button signal
      {
            //changing the speed every time a button is pressed
          switch(maxSpeed){
            case 20:
            maxSpeed = 40;
            break;
            case 40:
            maxSpeed = 20;
            break;
          }
     
      while ( debounce() ) ;  // wait for button release
      }
      
     
      int val = analogRead(Y_axis); //reading analog value of Yaxis
      
      
      //  min speed = 5 to max speed
      if ( speed_ != map(val, 0, 1023, maxSpeed, 5) )
      {
        // if the speed was changed
        if(val<504){
          speed_ = map(val, 0, 504, maxSpeed, 5);// map digital value from [0, 504] to [5, maxSpeed]
        }
        else if(val>520){
          speed_ = map(val, 520, 1023, 5, maxSpeed);// map digital value from [520, 1023] to [5, maxSpeed]
        }
        else{
          speed_ = 0; //motor not moving
        }
        // set the speed of the motor
          stepper.setSpeed(speed_);
      }
        
        if(val>520){
          direction_=1; //move forward
        }
        else if(val<504){
          direction_=-1; // move backward
        }
        else{
          direction_=0;  //stop
        }
      
      stepper.step(direction_);// move the stepper motor
      
      LCD.setCursor(0,0);
      LCD.print("max:");
      LCD.print(maxSpeed);
      LCD.setCursor(7,0);
      LCD.print("speed:");
      LCD.print(speed_);
      
      }

// a small function for button debounce
      bool debounce()
      {
        byte count = 0;
        
        for(byte i = 0; i < 5; i++) {
          if (digitalRead(button) == 0)
          count++;
          delay(10);
        }
        
        if(count > 2)  return 1;
        else           return 0;
      }

int getGps(){

}
void sendSMS(){

}
void tempratureControl(){

}
