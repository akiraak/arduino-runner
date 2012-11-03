#include <stdio.h>
#include <SerialLCD.h>
#include <SoftwareSerial.h>

#define SCENE_RELEASE (1)
#define SCENE_DIGITAL_TEST (100)
#define SCENE_ANALOG_TEST (101)
#define SCENE (SCENE_RELEASE)

static int slcdPin1 = 11;
static int slcdPin2 = 12;
SerialLCD slcd(slcdPin1,slcdPin2);

void setup() {
  Serial.begin(9600);
  Serial.println("==== start ====");
  slcd.begin();
  slcd.print("start");

#if SCENE == SCENE_RELEASE
  release_setup();
#elif SCENE == SCENE_SWITCH_TEST
  digital_test_setup();
#elif SCENE == SCENE_ANALOG_TEST
  analog_test_setup();
#endif
}

void loop() {
#if SCENE == SCENE_RELEASE
  release_loop();
#elif SCENE == SCENE_DIGITAL_TEST
  digital_test_loop();
#elif SCENE == SCENE_ANALOG_TEST
  analog_test_loop();
#endif
}

