#include <Servo.h> // include Servo library 



//--------------------------------------------------------------------------------//
// This is partially submitted as requirement for Tinkering Lab exercise 
// Name of the Students
// Ankit Das
// Arnav Gupta
// Anvesh Patel
// Aswin Suresh
// -------------
// github : https://github.com/nkitan/SolarTracker
// ------------------------------------------------------------------------------//

// 180 horizontal MAX
Servo Horizontal; // horizontal servo
int ServoHorizontal = 180;   // 90;     // stand horizontal servo

int servohLimitHigh = 180;
int servohLimitLow = 65;

// 65 degrees MAX
Servo Vertical;   // vertical servo 
int ServoVertical = 45;    //   90;     // stand vertical servo

int servovLimitHigh = 80;
int servovLimitLow = 15;


// LDR pin connections

int TopLeftLDR = 3; //LDR top left - BOTTOM LEFT    <--- BDG      
int TopRightLDR = 1; //LDR top rigt - BOTTOM RIGHT 
int DownLeftLDR = 2; //LDR down left - TOP LEFT
int DownRightLDR = 0; //ldr down rigt - TOP RIGHT                  

void setup()
{
  Serial.begin(9600);
  
   // SERVO CONNECTIONS
  
   Horizontal.attach(9);   // SERVONAME.ATTACH(PIN);
   Vertical.attach(10);
   Horizontal.write(180);
   Vertical.write(45);
   delay(3000);
}

void loop() 
{
  int debug = 1;
  int TopLeft = analogRead(TopLeftLDR); // top left
  int TopRight  = analogRead(TopRightLDR); // top right
  int DownLeft   = analogRead(DownLeftLDR); // down left
  int DownRight = analogRead(DownRightLDR); // down rigt
  int DelayTime = 10;  // DELAY TIME
  int Tolerance = 50;    // TOLERANCE
  
  int TopAverage = (TopLeft + TopRight) / 2; // average value top
  int DownAverage = (DownLeft + DownRight) / 2; // average value down
  int LeftAverage = (TopLeft + DownLeft) / 2; // average value left
  int RightAverage = (TopRight + DownRight) / 2; // average value right

  int VerticalDifference = TopAverage - DownAverage; // check the diffirence of up and down
  int HorizontalDifference = LeftAverage - RightAverage;// check the diffirence og left and rigt



  // DEBUGGING
                                                          
  if(debug == 0){                                             // ENABLING DEBUGGING CAUSES SLOW EXECUTION 
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
    ServoVertical = ++ServoVertical;                           // INCREMENTS SERVO VERTICAL
     if (ServoVertical > servovLimitHigh)  
      ServoVertical = servovLimitHigh;                  // LIMITS SERVO TO UPPER LIMIT
    }
    else if (TopAverage < DownAverage)
    {
     ServoVertical= --ServoVertical;
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
    ServoHorizontal = --ServoHorizontal;
    if (ServoHorizontal < servohLimitLow)
     ServoHorizontal = servohLimitLow;                         
   }
  else if (LeftAverage < RightAverage)
  {
    ServoHorizontal = ++ServoHorizontal;
     if (ServoHorizontal > servohLimitHigh)
     ServoHorizontal = servohLimitHigh;
  }
  else if (LeftAverage == RightAverage)
  {
    ServoHorizontal = 90;
  }
  Horizontal.write(ServoHorizontal);
  }
   delay(DelayTime);
}
