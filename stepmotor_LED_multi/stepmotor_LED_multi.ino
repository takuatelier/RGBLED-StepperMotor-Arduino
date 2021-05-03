#include <TimedAction.h>

// Steping Motor Driver Pin
const int APHASE  = 4;
const int AENBL   = 5;
const int BPHASE  = 6;
const int BENBL   = 7;

// Full Color LED Pin
const int LED_PIN_R = 8;
const int LED_PIN_G = 9;
const int LED_PIN_B = 10;
int LED_WAIT = 10;

// Volume Pin & value
const int VOLUME_MOTOR = A7;
const int VOLUME_LED = A6;

// Volume_value function
float volume_value();

// Led functions
void led_turnon();
void led_turnoff();
void led_blinking();
void led_fullcolor_turnon();
void led_fullcolor_blinking();
void led_control();

// Stepper motor functions
void delay_wait();
void stepper_rotate();
void stepper_control();

TimedAction motorAction = TimedAction(3000,stepper_control);
TimedAction ledAction = TimedAction(2000,led_control);

void setup() {
  pinMode(APHASE,OUTPUT);
  pinMode(AENBL,OUTPUT);
  pinMode(BPHASE,OUTPUT);
  pinMode(BENBL,OUTPUT);
  digitalWrite(AENBL,HIGH);
  digitalWrite(BENBL,HIGH);
  Serial.begin(9600);
}

void loop() {
  motorAction.check();
  ledAction.check();
}


float volume_value(int pin_num){
  float volume = analogRead(pin_num);
  volume = volume / 3.788;
  Serial.println(volume, 3);
  delay(100);

  return volume;
}

// LED Turn on Red, Green, Blue
void led_turnon(int pin_num){
  analogWrite(pin_num,0);
  delay(3000);
}

// LED Turn off
void led_turnoff(){
  analogWrite(LED_PIN_R,255);
  analogWrite(LED_PIN_G,255);
  analogWrite(LED_PIN_B,255);
  delay(3000);
}

// LED Blinking Red, Green, Blue
void led_blinking(int pin_num){
  for(int i=510; i>0; i--){
    analogWrite(pin_num, abs(i-255));
    delay(LED_WAIT);
  }
}

// LED Turn on White
void led_fullcolor_turnon(){
  analogWrite(LED_PIN_R,0);
  analogWrite(LED_PIN_G,0);
  analogWrite(LED_PIN_B,0);
  delay(3000);
}

// LED Blinking White
void led_fullcolor_blinking(){
  for(int i=510; i>0; i--){
    analogWrite(LED_PIN_R, abs(i-255));
    analogWrite(LED_PIN_G, abs(i-255));
    analogWrite(LED_PIN_B, abs(i-255));
    delay(LED_WAIT);
  }
}

void led_control(){
  float value_led = volume_value(VOLUME_LED);

  if(value_led>=0 && value_led<30) {
    Serial.println("Sleep LED");
    led_turnoff();
  }
  else if(value_led>=30 && value_led<60) { 
    Serial.println("Turn On Red LED");
    led_turnon(LED_PIN_R);
  }
  else if(value_led>=60 && value_led<90) { 
    Serial.println("Turn On Green LED");
    led_turnon(LED_PIN_G);
  }
  else if(value_led>=90 && value_led<120) { 
    Serial.println("Turn On Blue LED");
    led_turnon(LED_PIN_B);
  }
  else if(value_led>=120 && value_led<150) { 
    Serial.println("Turn On White LED");
    led_fullcolor_turnon();
  }
  else if(value_led>=150 && value_led<180) { 
    Serial.println("Blinking Red LED");
    led_blinking(LED_PIN_R);
  }
  else if(value_led>=180 && value_led<210) { 
    Serial.println("Blinking Green LED");
    led_blinking(LED_PIN_G);
  }
  else if(value_led>=210 && value_led<240) { 
    Serial.println("Blinking Blue LED");
    led_blinking(LED_PIN_B);
  }
  else if(value_led>=240 && value_led<271) { 
    Serial.println("Blinking White LED");
    led_fullcolor_blinking();
  }  
}

void delay_wait(int step_speed = 15){
  delay(step_speed); //max5 min 25
}

void stepper_rotate(int step_speed){
  for (int i = 0; i < 100; i++) { 
    //delay 7 ;  i < 100 : 360° i < 50 : 180° i < 25 : 90°
    digitalWrite(APHASE, HIGH);
    delay_wait(step_speed);               
    digitalWrite(BPHASE, HIGH); 
    delay_wait(step_speed);              
    digitalWrite(APHASE, LOW); 
    delay_wait(step_speed);             
    digitalWrite(BPHASE, LOW);  
    delay_wait(step_speed);             
  }
}

void stepper_control(){
  int rotate_count = 5;
  int step_speed;
  float value = volume_value(VOLUME_MOTOR);
  
  if(value>=0 && value<45) {
    Serial.println("Sleep Stepping Motor");
  }
  else if(value>=45 && value<90) { 
    step_speed = 25;
    Serial.println("Very Low Speed Rotation");
    for (int cnt = 0; cnt < rotate_count; cnt++) {    
      stepper_rotate(step_speed); 
    }
  }
  else if(value>=90 && value<135) { 
    step_speed = 20;
    Serial.println("Low Speed Rotation");
    for (int cnt = 0; cnt < rotate_count; cnt++) {    
      stepper_rotate(step_speed); 
    }
  }
  else if(value>=135 && value<180) { 
    step_speed = 15;
    Serial.println("middle Speed Rotation");
    for (int cnt = 0; cnt < rotate_count; cnt++) {    
      stepper_rotate(step_speed); 
    }
  }
  else if(value>=180 && value<225) { 
    step_speed = 10;
    Serial.println("High Speed Rotation");
    for (int cnt = 0; cnt < rotate_count; cnt++) {    
      stepper_rotate(step_speed); 
    }
  }
  else if(value>=225 && value<280) { 
    step_speed = 5;
    Serial.println("Very High Speed Rotation");
    for (int cnt = 0; cnt < rotate_count; cnt++) {    
      stepper_rotate(step_speed); 
    }
  }
  Serial.println("Break Time");  
}
