// Do not remove the include below
#include "Servo_Steller_Test.h"
#include <Arduino.h>
#include <Steller.h>

Steller steller[6];
String name[6] = { "S4", "S5", "S1", "S6", "S2", "S3" };
int upright[6] = { 66, 99, 90, 51, 71, 94 };
int flat[6] = { 161, 7, 4, 147, 166, 4 };
int analogPin[6] = { 0, 1, 2, 3, 4, 5 };
int pwmPin[6] = { 12, 11, 10, 9, 8, 7 };

//The setup function is called once at startup of the sketch
void setup() {
	for (int i = 0; i < 6; i++) {
		steller[i].setAngles(flat[i], upright[i]);
		steller[i].setPins(analogPin[i], pwmPin[i]);
		steller[i].Steller::attach();
	}

}

// The loop function is called in an endless loop
void loop() {
	for (int i = 0; i < 6; i++) {
		steller[i].stelle(60);
	}
	delay(5000);
}
