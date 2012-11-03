#include <stdio>

namespace analog_test {
  
static int sensorPin = 0;
static unsigned int counter = 0;

void setup(){
  Serial.println("MODE: analog_test");
}

void loop() {
  int data = analogRead(sensorPin);
  char buf[256];
  sprintf(buf, "%d DATA: %d", counter, data);
  counter++;
  Serial.println(buf);

  slcd.clear();
  slcd.setCursor(0, 0);
  slcd.print((long unsigned int)data,DEC);

  delay(100);
}

};

void analog_test_setup() {
  analog_test::setup();
}
void analog_test_loop() {
  analog_test::loop();
}
