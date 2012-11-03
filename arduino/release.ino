#include <stdio>

//#define LENGTH_RUNNER (2585L)
#define LENGTH_RUNNER (2530L)

#define ONE_TIME_TO_MMPH (x) (LENGTH_RUNNER * x / (3600))
#define MIN_ON_TIME (400)

namespace release {
  
static int sensorPin = 2;
static boolean sensor = false;
static boolean prevSensor = 0;
static unsigned long counter = 0;

static unsigned long prevOnTime = 0;
static unsigned long totalTime = 0;
static unsigned long loopCount = 0;


/*
  return: m/h
 */
unsigned long oneTime2mmph(unsigned long elapsedTime) {
  return LENGTH_RUNNER * 3600 / elapsedTime;
}


void setup(){
  pinMode(sensorPin, INPUT);
  //slcd.setCursor(0, 0);
  //slcd.print(1.0f, 1);
}

void print_console(float kmph, float total, unsigned long time) {
  Serial.print("Speed:");
  Serial.print(kmph);
  Serial.print("km/h ");

  Serial.print("Dist:");
  Serial.print(total / 1000000.0f);
  Serial.print("km ");

  Serial.print("Time:");
  long unsigned int s = time / 1000;
  long unsigned int s_s = s % 60;
  long unsigned int m = s / 60;
  long unsigned int s_m = m % 60;
  long unsigned int h = m / 60;
  Serial.print(h, DEC);
  Serial.print(":");
  if(s_m < 10)
    Serial.print("0");
  Serial.print(s_m, DEC);
  Serial.print(":");
  if(s_s < 10)
    Serial.print("0");
  Serial.print(s_s, DEC);
  Serial.print("\n");
}

void print_lcd(float kmph, float total, unsigned long time) {
  slcd.setCursor(0, 0);
  slcd.print(kmph, 2);
  slcd.print("km/h     ");

  slcd.setCursor(0, 1);
  slcd.print(total / 1000000.0f, 2);
  slcd.print("km ");

  long unsigned int s = time / 1000;
  long unsigned int s_s = s % 60;
  long unsigned int m = s / 60;
  long unsigned int s_m = m % 60;
  long unsigned int h = m / 60;
  slcd.print(h, DEC);
  slcd.print(":");
  if(s_m < 10)
    slcd.print("0");
  slcd.print(s_m, DEC);
  slcd.print(":");
  if(s_s < 10)
    slcd.print("0");
  slcd.print(s_s, DEC);
  slcd.print("                  ");
}

void print_data(float kmph, float total, unsigned long time) {
  print_console(kmph, total, time);
  print_lcd(kmph, total, time);
}

void loop() {

  //unsigned long nowTime = millis();
  // unsigned long elapsedTime = nowTime - time;
  //if(elapsedTime > 1000){
  //  elapsedTime = 0;
  //}
  //time = nowTime;

  sensor = digitalRead(sensorPin) == 1;
  /*
  if(counter % 100000 == 0){
   sensor = true;
   }else{
   sensor = false;
   }
   counter++;
   */

  if(prevSensor != sensor){
    if(sensor){
      unsigned long nowTime = millis();
      //oneTime2kmph(elapsedTime);
      unsigned long elapsedOnTime = nowTime - prevOnTime;
      totalTime += elapsedOnTime;

      if(elapsedOnTime > MIN_ON_TIME){
        loopCount++;
        float kmph = oneTime2mmph(elapsedOnTime) / 1000.0f;
        //char buf[256];
        //sprintf(buf, "%d millis:%d/%d time:%d km/h:%d", counter, lookTime, prevLookTime, time, kmph);
        Serial.print(kmph);
        Serial.print("km/h");

        float totalKmm = loopCount * LENGTH_RUNNER;
        Serial.print(" total:");
        if(totalKmm < 1000000){
          Serial.print(totalKmm / 1000);
          Serial.print("m");
        }
        else{
          Serial.print(totalKmm);
          Serial.print("km");
        }
        Serial.print(" elapsedTime:");
        Serial.print(elapsedOnTime);
        Serial.print("msec");
        prevOnTime = nowTime;
        Serial.print("\n");
        
        print_data(kmph, totalKmm, totalTime);
      }
    }
  }
  prevSensor = sensor;
}

};

void release_setup() {
  release::setup();
}
void release_loop() {
  release::loop();
}


