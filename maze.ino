#include <QTRSensors.h>
//#define QTR_NO_EMITTERS_PIN 2
#define rightMotorF 4
#define rightMotorB 5
#define rightMotorPWM 3
#define leftMotorF 7
#define leftMotorB 8
#define leftMotorPWM 9
#define stby 6

#define NUM_SENSORS  8   // number of sensors used
#define TIMEOUT       3000  // waits for 3000 us for sensor outputs to go low
//#define Tnum_sensor 2
 //int k, led=12,m=2;
QTRSensorsRC qtrrc((unsigned char[]) {A0,A1,A2,A3,A4,A5,11,12},  NUM_SENSORS, TIMEOUT); //QTR_NO_EMITTER_PIN); 
//QTRSensorsRC qtrrc1((unsigned char[]) {10,11}, Tnum_sensor, TIMEOUT); //QTR_NO_EMITTER_PIN); 

unsigned int sensorValues[NUM_SENSORS];
//unsigned int sensor[Tnum_sensor];
 unsigned int last_proportional = 0;
 long integral = 0;
 ;
  
void setup()
{
  pinMode(10, INPUT);
  pinMode(11, INPUT);
 //pinMode(led, OUTPUT);
  //pinMode(m, INPUT);
 
 
  pinMode(rightMotorF, OUTPUT); 
  pinMode(rightMotorB, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(rightMotorF, OUTPUT);
  pinMode(rightMotorB, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(stby,OUTPUT);
  
  Serial.begin(9600);
  
 delay(350);
 int k;
for (k = 0; k < 150; k++) // make the calibration take about 5 seconds
{
qtrrc.calibrate();
//qtrrc1.calibrate();
delay(20);
//Serial.println(k);
}
delay(20);
}

void loop()
{
//qtrrc1.readLine(sensor);
const int maximum = 150;

int position = qtrrc.readLine(sensorValues); // get calibrated readings along with the line position, refer to the QTR Sensors Arduino Library for more details on line position.
//Serial.println(position);

//Maths Part
 int proportional = -int(position)+3500;
 int derivative = proportional-last_proportional;
 integral+=proportional ;
last_proportional = proportional;
 
  
    int power_difference = proportional*1/5 + integral/10000 + derivative*9/4;

  if (power_difference > maximum)
    power_difference = maximum;
  if (power_difference < -maximum)
    power_difference = -maximum;

//Motor Motion
  if (power_difference < 0)//left 
  {
 digitalWrite(rightMotorF, HIGH);
  digitalWrite(rightMotorB, LOW);
  analogWrite(rightMotorPWM, maximum);
    digitalWrite(leftMotorF, HIGH);
  digitalWrite(leftMotorB, LOW);
  analogWrite(leftMotorPWM, maximum + power_difference);
  digitalWrite(stby,HIGH);
  
  }
  else //right
{ 
 digitalWrite(rightMotorF, HIGH);
  digitalWrite(rightMotorB, LOW);
  analogWrite(rightMotorPWM,maximum - power_difference);
    digitalWrite(leftMotorF, HIGH);
  digitalWrite(leftMotorB, LOW);
  analogWrite(leftMotorPWM, maximum);
  digitalWrite(stby,HIGH);
  
}
qtrrc.readCalibrated(sensorValues);
//qtrrc1.readCalibrated(sensor);
 
 //int a=analogRead(m);
 //if(a>50)
 //{
   //stop1();
   //delay(5000);
 //digitalWrite(led,HIGH);
 //}
 
 if(sensorValues[0]>300 && sensorValues[1]>300 && sensorValues[2]>300 && sensorValues[3]>300 && sensorValues[4]>300  &&sensorValues[6]>300 && sensorValues[7] > 300 )  //u-turn //black
   { 
      
      backward();
       
    }
if(( sensorValues[2] >350 &&sensorValues[3] >350 && sensorValues[4] >350 &&sensorValues[5] >350 )&& ((sensorValues[0]>350&& sensorValues[1]>350) || (sensorValues[7] >350&& sensorValues[6]>350))) 

    {
     maze();
                                       
    }
}

void left()
 { 
digitalWrite(rightMotorF, HIGH);
  digitalWrite(rightMotorB,LOW);
  analogWrite(rightMotorPWM,100 );
    digitalWrite(leftMotorF,LOW);
  digitalWrite(leftMotorB, HIGH);
  analogWrite(leftMotorPWM, 100);
  digitalWrite(stby,HIGH);
 }
  void straight()
  {
  digitalWrite(rightMotorF,HIGH);
  digitalWrite(rightMotorB,LOW);
  analogWrite(rightMotorPWM,75);
    digitalWrite(leftMotorF,HIGH);
  digitalWrite(leftMotorB, LOW);
  analogWrite(leftMotorPWM, 75);
  digitalWrite(stby,HIGH);
  }
  void right()
  {    
   digitalWrite(rightMotorF,LOW);
  digitalWrite(rightMotorB, HIGH);
  analogWrite(rightMotorPWM,100 );
    digitalWrite(leftMotorF, HIGH);
  digitalWrite(leftMotorB, LOW);
  analogWrite(leftMotorPWM, 100);
  digitalWrite(stby,HIGH);
   }
  void stop1()
   {
    digitalWrite(rightMotorF,LOW);
  digitalWrite(rightMotorB, LOW);
  analogWrite(rightMotorPWM,0 );
    digitalWrite(leftMotorF, LOW);
  digitalWrite(leftMotorB, LOW);
  analogWrite(leftMotorPWM, 0);
  digitalWrite(stby,LOW);
   }
    void backward()// perfect but worked once
{
   digitalWrite(rightMotorF,HIGH);
  digitalWrite(rightMotorB, LOW);
  analogWrite(rightMotorPWM,150 );
    digitalWrite(leftMotorF, LOW);
  digitalWrite(leftMotorB, HIGH);
  analogWrite(leftMotorPWM, 150);
  digitalWrite(stby,HIGH);
  delay(300);

  
  }


    void maze()
 {    

/*  int a=analogRead(m);
 if(a>50)
 {
    stop1();
   delay(5000);
 digitalWrite(led,HIGH);
 }
  */
      qtrrc.readLine(sensorValues);
     //qtrrc1.readLine(sensor);
//
  //    
    // if(sensorValues[0]<50 && sensorValues[1]<50 && sensorValues[2]<50 && sensorValues[3]<50 && (sensorValues[4]>80 || sensorValues[4]<50) && sensorValues[5]>80 && sensor[0]>80 && sensor[1]>80 )  //left
 //
 //
 // if(sensorValues[7]<350 && sensorValues[6]<350 && sensorValues[5]<350 && sensorValues[4]<350 && sensorValues[3]<350  &&sensorValues[1]>350 && sensorValues[0] > 350 )  //left
  //{
 //straight();
 //delay(275);
    //     
   // left();
     //delay(450);
  //      
  //}  
  //else
  //if(sensorValues[0]>80 && (sensorValues[1]<50 || sensorValues[1]>80) && sensorValues[2]<50 && sensorValues[3]<50 && sensorValues[4]<50 && sensorValues[5]<50 && sensor[0]>80 && sensor[1]>80 )// right
  //if(sensorValues[0]<350 && sensorValues[1]<350 && sensorValues[2]<350 && sensorValues[3]<350 && sensorValues[4]<350  &&sensorValues[6]>350 && sensorValues[7] > 350 ) // right
    // {
    //   straight();
     //delay(275);
       //right();
         //     delay(300);
             
       
    //    }

     if(  sensorValues[2]<350 && sensorValues[3]<350 && sensorValues[4]<350 && sensorValues[5]<350  &&(sensorValues[6]<350 ||sensorValues[7]<350 ) ) //tpoiont
     {
        //straight();
     //delay(275);
      stop1();
      delay(2000);
                left();
                delay(450);
                
      }
   /*else
   if(sensorValues[0]>80 && sensorValues[5]>80 && sensorValues[0]>80 && sensorValues[1]>80)   //plus-point
  { 
     straight();
     delay(275);
      
    left();
   delay(300);
    
  }
  */
else
       if(sensorValues[0]<350 && sensorValues[1]<350 && sensorValues[2]<350 && sensorValues[3]<350 && sensorValues[4]<350   )  //st-right
        {
      
          straight();
        delay(275);
          
           }
           
          /* else
       if(sensorValues[0]>350 && sensorValues[1]>350 && sensorValues[2]>350 && sensorValues[3]>350 && sensorValues[4]>350  &&sensorValues[6]>350 && sensorValues[7] > 350 )  //u-turn
        {
      
          backward();
        delay(275);
          
           }*/
    else
         if(sensorValues[7]<250 && sensorValues[6]<250 && sensorValues[5]<250 && sensorValues[4]<250 && sensorValues[3]<250    )  //straight-left
    { 
     // stop1();
      //delay(800);
    //straight();
     //delay(275);

//stop1();
  //    delay(800);
      
      left();
     delay(550);
//stop1();
  //    delay(800);

     }
    
 
 }
  
