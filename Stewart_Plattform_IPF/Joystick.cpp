/*
 * Joystick.cpp
 *
 *  Created on: 21.10.2015
 *      Author: Nils
 */

#include "Joystick.h"

Joystick::Joystick(int x0Wert, int y0Wert, int xAxPin, int yAxPin) {
	this->_x0Wert = x0Wert;
	this->_y0Wert = y0Wert;
	this->_xAxPin = xAxPin;
	this->_yAxPin = yAxPin;
}
Joystick::~Joystick() {
	// TODO Auto-generated destructor stub
}

int Joystick::geglaettet(int eingang) {
	int messwerte;
	int i = 1;
	while (i < 6) {
		messwerte = messwerte + analogRead(eingang);
		i++;
	}
	int ergebnis = messwerte / i;
	return ergebnis;
}

Vector Joystick::bewegung(int modus) {
	Vector bewegung;
	int auslenkung;
	int warten;
}

