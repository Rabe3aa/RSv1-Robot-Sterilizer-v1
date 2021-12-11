#include <Servo.h> //the servo library
Servo myservo;
int pos = 0;
//attaching the left motor to arduino pins
int motor_L1 = 8;
int motor_L2 = 9;
int enable_L = 7;
//attaching the right motor to arduino pins
int motor_R1 = 10;
int motor_R2 = 11;
int enable_R = 12;
//attaching the ultrasonic to arduino pins
const int trig = 2;
const int echo = 3;
//attaching the servo motor sinal to arduino pins
int servo_motor = 4;

int limits = 25;// the limit of available space of the obstacle
int i;
int x = 0;
unsigned long time;
int range;
int distance_left, distance_right;
int max_speed = 30;

void the_distance();
void go_straight(int way);
void go_left();
void go_right();
void move_back_and_forth();
void motor_reset();
void turn_right();
void turn_left();

void setup() 
{
  Serial.begin(9600);
  myservo.attach(4);
  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT);

  pinMode(motor_L1,OUTPUT);
  pinMode(motor_L2,OUTPUT);
  pinMode(motor_R1,OUTPUT);
  pinMode(motor_R2,OUTPUT);

  digitalWrite(enable_L, HIGH);
  digitalWrite(enable_R, HIGH);
  
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_R1, LOW);
  digitalWrite(motor_R2, LOW);

  myservo.write(90);
  delay(500);
}

void loop() {
range = 0;
  the_distance();
  Serial.println(range);
  if (range > limits)
  {
    go_straight();
  }
  else
  {
    motor_reset();
    move_back();
    delay(300);
    motor_reset();
    turn_left();
    the_distance();
    distance_left = range;
    turn_right();
    the_distance();
    distance_right = range;
    if ( distance_right < 30 &&  distance_left < 30) {
      move_back();
      delay(1000);
      motor_reset();
      delay(1000);
      go_right();
    }
    else
    {
      if ( distance_right >=  distance_left)
      {
        go_right();
        delay(100);
      }
      if ( distance_right <  distance_left)
      {
        go_left();
        delay(100);
      }
    }
  } 
}

void motor_reset()
{
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_R1, LOW);
  digitalWrite(motor_R2, LOW);
}

void go_straight()
{
  
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_R1, HIGH);
  digitalWrite(motor_R2, LOW);
}

void go_right()
{
  motor_reset();
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_R2, HIGH);
  digitalWrite(motor_R1, LOW);
  delay(600);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_R2, LOW);
}

void go_left()
{
  motor_reset();
  digitalWrite(motor_R1, HIGH);
  digitalWrite(motor_R2, LOW);
  digitalWrite(motor_L2, HIGH);
  digitalWrite(motor_L1, LOW);
  delay(600);
  digitalWrite(motor_R1, LOW);
  digitalWrite(motor_L2, LOW);
}

void move_back()
{
  digitalWrite(motor_L2, HIGH);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_R2, HIGH);
  digitalWrite(motor_R1, LOW);
}

void the_distance()
{

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);


  // Measure HIGH pulse width at echo pin.
  time = pulseIn(echo, HIGH);

  range =  time*0.034/2;
}

void turn_left()
{
  myservo.write(180);              // tell servo to go to position in variable 'pos'
  delay(1000);
  the_distance();
  myservo.write(90);              // tell servo to go to position in variable 'pos'
}

void turn_right()
{
  myservo.write(0);              // tell servo to go to position in variable 'pos'
  delay(1000);
  the_distance();
  myservo.write(90);              // tell servo to go to position in variable 'pos'
}

void resetservo()
{
  myservo.write(90);
}
