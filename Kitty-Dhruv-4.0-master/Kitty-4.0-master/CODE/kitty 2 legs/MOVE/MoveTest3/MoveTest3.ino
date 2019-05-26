#include <PinChangeInt.h>

#define motor1  38
#define motor1pwm  10
#define motor2  17
#define motor2pwm  9

int A_1 = 5, A_2 = -1;

#define a1 A14
#define b1 A15
#define a2 A12
#define b2 A13

//bool state1 = true, state2 = true;

float pwmx1=100, pwmx2=50, pwmx4=150;
float theta1c=0, theta2c=0, zeroError1 = 56.6296, zeroError2 = 39.0143, minAngle1 = 21.3, minAngle2 = 30.0;  //zeroError1 = 69.513, zeroError2=51.58
int x;

volatile int temp1, counter1 = 0; 
volatile int temp2 , counter2 = 0;

void setup() {
  Serial.begin(9600);
  //Pins for encoders
  pinMode(a1, INPUT_PULLUP);                                           
  pinMode(b1, INPUT_PULLUP);
  PCintPort::attachInterrupt(A_1, ai2_3, CHANGE);
//  state1 = digitalRead(a1);
  
  pinMode(a2, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  PCintPort::attachInterrupt(A_2, ai3_3, CHANGE);
//  state2 = digitalRead(a2);
  
  //Pins for Motors
  pinMode(motor1, OUTPUT);
  pinMode(motor1pwm, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor2pwm, OUTPUT);

}

void loop() {
  if (Serial.available())
  {
    x = Serial.parseInt();
  }
    if ( x ) {
      if (x < 3)
      {       
        digitalWrite(motor1, x - 1 );
        if(x==1)
        analogWrite(motor1pwm , pwmx1);
        else
        analogWrite(motor1pwm , pwmx2);
        
      }
      if(x == 3 || (-theta1c+minAngle1)>zeroError1){         //62.513 65.0187
        analogWrite(motor1pwm , 0);
        x=3;
        }
      if(x>3 && x<6){
        digitalWrite(motor2, x - 4 );
        analogWrite(motor2pwm , pwmx4);
        }
      if(x == 6 || (-theta2c+minAngle2)>zeroError2){           //51.58 51.66
        analogWrite(motor2pwm , 0);
        x=6;
        }
    }
  

  //Convert Encoder Output into angle
      if(counter1 != temp1){
        temp1 = counter1;
        if(counter1 > 1200) {
          counter1 = 0;
         }
        theta1c = (counter1 * 0.3);
        Serial.println ("theta1");
        Serial.println (theta1c);
//        Serial.println(counter1);
     }
      if ( counter2 != temp2 ) {
        temp2 = counter2;
        if (counter2 > 1200) {
          counter2 = 0;
        }
        theta2c = -(counter2 * 0.3);
        Serial.println ("theta2");
        Serial.println (theta2c);
//        Serial.println(counter1);
    }
//      Serial.print("counter: ");
//      Serial.println(counter2);

}
// Encoder1
void ai2_3() {
  if (digitalRead(b1) == !digitalRead(a1)) {
    counter1++;
  } else {
    counter1--;
  }
//  state1 = !state1;
//  Serial.print("counter1: ");
//  Serial.println(counter1);
}

////  Encoder2
void ai3_3() {
  if (digitalRead(b2) == !digitalRead(a2)) {
    counter2++;
  } else {
    counter2--;
  }
//  state2 = !state2;
//  Serial.print("counter2: ");
//  Serial.println(counter2);
}
