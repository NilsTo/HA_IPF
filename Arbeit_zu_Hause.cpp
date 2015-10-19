// Do not remove the include below
#include "Arduino.h"
#include "Arbeit_zu_Hause.h"
#include "LiquidCrystal.h"

int posz = 0;
int posy = 0;
int posx = 0;
int pinz = 13;
int piny = 14;
int pinx = 15;
LiquidCrystal lcd(31,30,32,34,36,38);


void setup() {
	Serial.begin(9600);
	lcd.begin(16,2);
}

void loop() {
	posy = analogRead(piny);
	posx = analogRead(pinx);
	posz = analogRead(pinz);
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("y = ");
	lcd.print(posy);
	lcd.setCursor(0,1);
	lcd.print("x = ");
	lcd.print(posx);
	lcd.print(" z = ");
	lcd.print(posz);
	delay(500);
}
