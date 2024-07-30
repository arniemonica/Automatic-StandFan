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
int TLevel = 2;
float temperature;



void setup(){
pinMode (3, OUTPUT); 
pinMode(2, INPUT); 
dht.setup(7);
Serial.begin(9600);
}
void loop(){
  if(duration ==0){
   
    duration=duration + 1;
    Serial.println("0");
    delay(1000);
  }
  if(duration == 1){
    Serial.println("1");
     LowToNormal();
     duration=duration + 1;
  }
}  