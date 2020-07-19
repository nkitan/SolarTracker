#include <Servo.h> // include Servo library 

//--------------------------------------------------------------------------------//
// This is partially submitted as requirement for Tinkering Lab exercise 
// Coded by Ankit Das @ github.com/nkitan
// -------------
// github : https://github.com/nkitan/SolarTracker
// ------------------------------------------------------------------------------//


// Switches 
int debug = 0;        // Turn debugging on or off
int DelayTime = 10;   // delay time (in ms)
int Tolerance = 50;   // tolerance


// LDR pin connections
int TopLeftLDR = 3; //LDR top left - BOTTOM LEFT    <--- BDG      
int TopRightLDR = 1; //LDR top rigt - BOTTOM RIGHT 
int DownLeftLDR = 2; //LDR down left - TOP LEFT
int DownRightLDR = 0; //ldr down rigt - TOP RIGHT  


Servo Horizontal; // horizontal servo
Servo Vertical;   // vertical servo 

// initialize with Starting positions
int ServoHorizontal = 180;  
int ServoVertical = 45;

// Servo Movement limits
int servohLimitHigh = 180;
int servohLimitLow = 65;
int servovLimitHigh = 80;  
int servovLimitLow = 15;
                

void setup()
{
  Serial.begin(9600);
  
   // SERVO CONNECTIONS
   Horizontal.attach(9);   // SERVONAME.ATTACH(PIN);
   Vertical.attach(10);
   Horizontal.write(ServoHorizontal);  // set servos to initial Positions
   Vertical.write(ServoVertical);
   delay(3000);
}

void loop() 
{

  int TopLeft = analogRead(TopLeftLDR); // top left
  int TopRight  = analogRead(TopRightLDR); // top right
  int DownLeft   = analogRead(DownLeftLDR); // down left
  int DownRight = analogRead(DownRightLDR); // down rigt
  
  int TopAverage = (TopLeft + TopRight) / 2; // average value top
  int DownAverage = (DownLeft + DownRight) / 2; // average value down
  int LeftAverage = (TopLeft + DownLeft) / 2; // average value left
  int RightAverage = (TopRight + DownRight) / 2; // average value right

  int VerticalDifference = TopAverage - DownAverage; // check the diffirence of up and down
  int HorizontalDifference = LeftAverage - RightAverage;// check the diffirence og left and rigt



  // DEBUGGING
                                                          
  if(debug){                                             // ENABLING DEBUGGING CAUSES SLOW EXECUTION 
  Serial.print(" TAVG->");  
  Serial.print(TopAverage);             
  Serial.print(" DAVG->"); 
  Serial.print(DownAverage);
  Serial.print(" LAVG->");
  Serial.print(LeftAverage);
  Serial.print(" RAVG->");
  Serial.print(RightAverage);
  Serial.print("  DEL->");
  Serial.print(DelayTime);
  Serial.print("  TOL->");
  Serial.print(Tolerance);
  Serial.println(" ");
  }
    
  // CHECK FOR VERTICAL SERVO
  
  
  if (-1* Tolerance > VerticalDifference || VerticalDifference > Tolerance) // check if the diffirence is in the tolerance else change vertical angle
  {
   if (TopAverage > DownAverage)
    {
    ServoVertical++;                           // INCREMENTS SERVO VERTICAL
     if (ServoVertical > servovLimitHigh)  
      ServoVertical = servovLimitHigh;                  // LIMITS SERVO TO UPPER LIMIT
    }
    else if (TopAverage < DownAverage)
    {
     ServoVertical--;
    if (ServoVertical < servovLimitLow)
       ServoVertical = servovLimitLow;                  // LIMITS SERVO TO LOWER LIMIT
    }
   Vertical.write(ServoVertical);
  }


  // CHECK FOR HORIZONTAL SERVO
  
  
 if (-1*Tolerance > HorizontalDifference || HorizontalDifference > Tolerance) // check if the diffirence is in the tolerance else change horizontal angle
  {
  
  if (LeftAverage > RightAverage)
  {
    ServoHorizontal--;
    if (ServoHorizontal < servohLimitLow)
     ServoHorizontal = servohLimitLow;                         
   }
    
  else if (LeftAverage < RightAverage)
  {
     ServoHorizontal++;
     if (ServoHorizontal > servohLimitHigh)
     ServoHorizontal = servohLimitHigh;
   }
    
  else if (LeftAverage == RightAverage)
   Horizontal.write(ServoHorizontal);
   
  }
   delay(DelayTime);
}
