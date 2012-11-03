#include <stdio>

namespace digital_test {
  
static int sensorPin = 2;
static unsigned int counter = 0;

void setup(){
  Serial.println("MODE: digital_test");
  pinMode(sensorPin, INPUT);
}

void loop() {
  int data = digitalRead(sensorPin);
  char buf[256];
  sprintf(buf, "%d DATA: %d", counter, data);
  counter++;
  Serial.println(buf);

  slcd.clear();
  slcd.setCursor(0, 0);
  slcd.print((long unsigned int)data,DEC);

  delay(30);
}

};

void digital_test_setup() {
  digital_test::setup();
}
void digital_test_loop() {
  digital_test::loop();
}
