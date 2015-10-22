/*
 * Joystick.cpp
 *
 *  Created on: 21.10.2015
 *      Author: Nils
 */

#include "Joystick.h"

Joystick::Joystick(int x0Wert, int xMinWert, int xMaxWert, int y0Wert,
		int yMinWert, int yMaxWert, int xAxPin, int yAxPin) {
	this->_x0Wert = x0Wert;
	this->_xMinWert = xMinWert;
	this->_xMaxWert = xMaxWert;
	this->_y0Wert = y0Wert;
	this->_yMinWert = yMinWert;
	this->_yMaxWert = yMaxWert;
	this->_xAxPin = xAxPin;
	this->_yAxPin = yAxPin;
}
Joystick::~Joystick() {
	// TODO Auto-generated destructor stub
}

int Joystick::geglaettet(int eingang) {
	int messwerte = 0;
	int i = 1;
	while (i < 21) {
		messwerte = messwerte + analogRead(eingang);
		i++;
		delay(1);
	}
	float ergebnis = messwerte / i;
	return int(ergebnis);
}

Vector Joystick::bewegung(int modus) {
	Vector bewegung;
	int auslenkungX = _x0Wert - this->geglaettet(_xAxPin);
	int auslenkungY = _y0Wert - this->geglaettet(_yAxPin);
	if (auslenkungX < 0) {
		bewegung.x = (map(auslenkungX, 0, (_xMaxWert - _x0Wert), 0, 1000) / 1000.0f);
	} else {
		bewegung.x = (map(auslenkungX, 0, (_xMinWert - _x0Wert), 0, -1000) / 1000.0f);
	}
	if (auslenkungY < 0) {
		bewegung.y = (map(auslenkungY, 0, (_yMaxWert - _y0Wert), 0, 1000) / 1000.0f);
	} else {
		bewegung.y = (map(auslenkungY, 0, (_yMinWert - _y0Wert), 0, -1000) / 1000.0f);
	}
	bewegung.z = 0;
	return bewegung;
}

