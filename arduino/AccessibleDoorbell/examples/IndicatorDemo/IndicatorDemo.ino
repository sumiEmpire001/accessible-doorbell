#include <Arduino.h>
#include <AccessibleDoorbell.h>
// LEDs represent visual, haptic and audio notifications; no motor or buzzer.
// Simulated clock advances one hour each 10 seconds; real use requires RTC.
#if defined(ARDUINO_ARCH_ESP32)
const int BUTTON_PIN=27,VISUAL_LED=18,HAPTIC_LED=19,AUDIO_LED=21;
#else
const int BUTTON_PIN=2,VISUAL_LED=8,HAPTIC_LED=9,AUDIO_LED=10;
#endif
bool was_pressed=false;
doorbell::Doorbell controller;
void setup(){
 Serial.begin(115200);pinMode(BUTTON_PIN,INPUT_PULLUP);
 pinMode(VISUAL_LED,OUTPUT);pinMode(HAPTIC_LED,OUTPUT);pinMode(AUDIO_LED,OUTPUT);
 digitalWrite(VISUAL_LED,LOW);digitalWrite(HAPTIC_LED,LOW);digitalWrite(AUDIO_LED,LOW);
}
void loop(){
 bool pressed=digitalRead(BUTTON_PIN)==LOW;
 if(pressed&&!was_pressed){
  int simulated_hour=static_cast<int>((millis()/10000UL)%24);
  doorbell::Result r=controller.press(millis()/1000.0,simulated_hour);
  if(r.valid&&r.accepted){
   digitalWrite(VISUAL_LED,r.visual?HIGH:LOW);
   digitalWrite(HAPTIC_LED,r.haptic?HIGH:LOW);
   digitalWrite(AUDIO_LED,r.audio?HIGH:LOW);
   delay(150);
   digitalWrite(VISUAL_LED,LOW);digitalWrite(HAPTIC_LED,LOW);digitalWrite(AUDIO_LED,LOW);
  }
  Serial.print("hour_simulated=");Serial.print(simulated_hour);
  Serial.print(" accepted=");Serial.println(r.accepted);
 }
 was_pressed=pressed;
 delay(10);
}
