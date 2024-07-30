#include <IRLibSendBase.h>
#include <IRLib_HashRaw.h>
#include "DHT.h"
DHT dht;

IRsendRaw mySender;

//ON/OFF
#define RAW_DATA_LEN 68
uint16_t rawDataON_OFF[RAW_DATA_LEN]={
	9090, 4494, 534, 594, 534, 594, 534, 598, 
	534, 594, 534, 598, 534, 594, 534, 598, 
	534, 594, 534, 1714, 538, 1714, 534, 1714, 
	534, 1714, 538, 1714, 534, 1714, 534, 1714, 
	538, 1710, 534, 598, 534, 598, 534, 1714, 
	534, 1714, 534, 1714, 534, 598, 534, 594, 
	534, 598, 530, 1714, 534, 1714, 534, 598, 
	530, 598, 534, 594, 538, 1710, 534, 1714, 
	534, 1714, 534, 1000};

//SPEED
#define RAW_DATA_LEN 68
uint16_t rawDataSPEED[RAW_DATA_LEN]={
	9086, 4498, 534, 594, 538, 594, 534, 598, 
	530, 598, 534, 598, 534, 594, 534, 598, 
	534, 594, 534, 1718, 530, 1718, 534, 1714, 
	534, 1714, 534, 1714, 534, 1714, 534, 1714, 
	534, 1714, 534, 598, 530, 1718, 530, 1718, 
	530, 598, 534, 1714, 534, 598, 534, 594, 
	534, 598, 534, 1714, 534, 594, 534, 598, 
	534, 1714, 534, 594, 534, 1714, 534, 1714, 
	534, 1718, 534, 1000};


void NormalToHigh_HighToNormal(){
  for(int x=0;x<=1;x++){
    mySender.send(rawDataSPEED, RAW_DATA_LEN, 36);
    Serial.print(x);
    delay(500);  
  }
}
void NormalToLow(){
 for(int x=0;x<=8;x++){
  mySender.send(rawDataSPEED, RAW_DATA_LEN, 36);
  Serial.print(x);
  delay(500);
  }
}
void HighToLow_LowToHigh(){
for(int x=0;x<=6;x++){
  mySender.send(rawDataSPEED, RAW_DATA_LEN, 36);
  Serial.print(x);
  delay(500);
  }
}
void LowToNormal(){
for(int x=0;x<=4;x++){
  mySender.send(rawDataSPEED, RAW_DATA_LEN, 36);
  Serial.print(x);
  delay(500);
  }
}




int pirsensor = 0;
int check = 0;
unsigned long myTime;
int duration = 0;
int start = 0;
int TLevel;
int babataas;
float temperature;

void Temp(){
  if (temperature <= 27){
    if (TLevel == 2){
      if (babataas==1){
        LowToNormal();
        babataas = 0;
      }
      else{
        NormalToLow();
      }
      TLevel = 1;
    }
    else if (TLevel == 3){
      HighToLow_LowToHigh();
      TLevel = 1;
    }
    else{
      TLevel = 1;
    }
  }
  else if (temperature >= 33){
    if (TLevel == 1){
      HighToLow_LowToHigh();
      TLevel = 3;
    }
    else if (TLevel == 2){
      NormalToHigh_HighToNormal();
      TLevel = 3;
    }
    else{
      TLevel = 3;
    }
  }
  else if(temperature >=28 || temperature <=32 ){
    if (TLevel == 1){
      LowToNormal();
      TLevel = 2;
    }
    else if (TLevel == 3){
      NormalToHigh_HighToNormal();
      TLevel = 2;
      babataas = 1;
    }
    else{
      TLevel = 2;
    }
  }
}

void setup(){
pinMode (3, OUTPUT); 
pinMode(2, INPUT); 
dht.setup(7);
Serial.begin(9600);
}
void loop(){
  pirsensor = digitalRead(2);
  delay(dht.getMinimumSamplingPeriod());
  temperature = dht.getTemperature();
  if (start == 0){
    if(pirsensor == HIGH){
      Serial.println("Simula");
      duration = 20000;
      mySender.send(rawDataON_OFF, RAW_DATA_LEN, 36);
      start = 1;
      TLevel=2;
      delay(1000);
    }
  }
  else{
    if (duration > 0){
      if(pirsensor == HIGH){
        Serial.println("On");
        duration = 20000;
        Serial.println(duration);
        Temp();
        Serial.println(temperature, 1);
        delay(1000);
      }
      else{
        Serial.println("Countdown");
        duration = duration - 1000;
        Serial.println(duration);
        Temp();
        Serial.println(temperature, 1);
        delay(1000);
      }
    }
    if (duration <= 0){
      Serial.println("Off");
      mySender.send(rawDataON_OFF, RAW_DATA_LEN, 36);
      duration = 0;
      start = 0; 
      delay(1000);
    }
  }
}  