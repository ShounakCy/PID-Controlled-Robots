#define rightMotorF 8
#define rightMotorB 9
#define rightMotorPWM 3
#define leftMotorF 8
#define leftMotorB 7
#define leftMotorPWM 9
//#define stby 6

void setup() {
  // put your setup code here, to run once:
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(rightMotorF, OUTPUT);
  pinMode(rightMotorB, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(leftMotorF, OUTPUT);
  pinMode(leftMotorB, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);
  //pinMode(stby,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(leftMotorPWM,135);
analogWrite(rightMotorPWM,135);
  digitalWrite(leftMotorB,HIGH);
digitalWrite(leftMotorF,LOW);
digitalWrite(rightMotorB,LOW);
digitalWrite(rightMotorF,HIGH);
 //digitalWrite(stby,HIGH);

}
