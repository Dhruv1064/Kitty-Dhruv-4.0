#include <PinChangeInt.h>

#define motor1  31
#define motor2  29
#define motor1pwm  5
#define motor2pwm  10
int A_1 = 2;

#define a1 21
#define a2 A11          
#define b1 33
#define b2 49

bool state1 = true, state2 = true;

float theta1c=0, theta2c=0;
int x = 0;

volatile int temp1, counter1 = 0;
volatile int temp2 , counter2 = 0;

void setup() {
  Serial.begin(9600);
  //Pins for encoders
  pinMode(a1, INPUT_PULLUP);                                           
  pinMode(b1, INPUT_PULLUP);
  attachInterrupt(A_1, ai1, CHANGE);
  
  pinMode(a2, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  PCintPort::attachInterrupt(a2, ai2, CHANGE);

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
    if (x) {
      if (x < 3)
      {
        digitalWrite(motor1, x - 1 );
        if(x==1)
        analogWrite(motor1pwm , 60);
        else
        analogWrite(motor1pwm , 40);
      }
      if(x == 3 || (-theta1c+26)>58.8795){       //57.053
        analogWrite(motor1pwm , 0);
        x=3;
        }
      if(x>3 && x<6){
        digitalWrite(motor2, x - 4 );
        analogWrite(motor2pwm , 50);
        }
      if(x == 6 || (-theta2c/4)>50.4){         //49.04
        analogWrite(motor2pwm , 0);
        x=6;
        }
    }
  

  //Convert Encoder Output into angle
      if ( counter1 != temp1 ) {
        temp1 = counter1;
        if (counter1 > 1200) {
          counter1 = 0;
         }
        theta1c = (counter1 * 0.3);
        Serial.println("theta1c");
        Serial.println(theta1c);
     }
      if ( counter2 != temp2 ) {
        temp2 = counter2;
        if (counter2 > 1200) {
          counter2 = 0;
        }
        theta2c = -(counter2 * 0.3);
        Serial.println("theta2c");
        Serial.println(theta2c/4);
      }
}

void ai1(){
  if(digitalRead(b1) == state1){
    counter1++;
  }
  else{
    counter1--;
  }
  state1 = !state1;
}

void ai2(){
  if(digitalRead(b2) == state2){
    counter2++;
  }
  else{
    counter2--;
  }
  state2 = !state2;
}

