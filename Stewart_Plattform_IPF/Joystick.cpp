/*
 * Joystick.cpp
 *
 *  Created on: 21.10.2015
 *      Author: Nils
 */

#include "Joystick.h"

Joystick::Joystick(int xMinWert, int xMaxWert, int yMinWert, int yMaxWert,
		int xAxPin, int yAxPin) {
	this->_xMinWert = xMinWert;
	this->_xMaxWert = xMaxWert;
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
	while (i < 11) {
		messwerte = messwerte + analogRead(eingang);
		i++;
		delayMicroseconds(250);
	}
	float ergebnis = messwerte / i;
	return int(ergebnis);
}

void Joystick::kalibrieren(){
	this->_x0Wert = this->geglaettet(_xAxPin);
	this->_y0Wert = this->geglaettet(_yAxPin);
}



/*
 * Gibt +1 oder -1 bei maximalen Ausschlag des Joysticks zurück.
 */
Vector Joystick::bewegung(int modus) {
	Vector bewegung;
	int auslenkungX = _x0Wert - this->geglaettet(_xAxPin);
	int auslenkungY = _y0Wert - this->geglaettet(_yAxPin);
	if (auslenkungX < 0) {
		bewegung.x = (map(auslenkungX, 0, (_xMaxWert - _x0Wert), 0, 1000)
				/ 1000.0f);
	} else {
		bewegung.x = (map(auslenkungX, 0, (_xMinWert - _x0Wert), 0, -1000)
				/ 1000.0f);
	}
	if (auslenkungY < 0) {
		bewegung.y = (map(auslenkungY, 0, (_yMaxWert - _y0Wert), 0, -1000)
				/ 1000.0f);
	} else {
		bewegung.y = (map(auslenkungY, 0, (_yMinWert - _y0Wert), 0, 1000)
				/ 1000.0f);
	}
	bewegung.z = 0;
	return bewegung;
}
/*
 * Gibt die Lage des Joysticks in Eulerwinkeln zurück +-25Grad
 */
Vector Joystick::ausrichtung() {
	Vector ausrichtung;
	int auslenkungX = _x0Wert - this->geglaettet(_xAxPin);
	int auslenkungY = _y0Wert - this->geglaettet(_yAxPin);
	if (auslenkungX < 0) {
		ausrichtung.x = (map(auslenkungX, 0, (_xMaxWert - _x0Wert), 0, 20000)
				/ 1000.0f);
	} else {
		ausrichtung.x = (map(auslenkungX, 0, (_xMinWert - _x0Wert), 0, -20000)
				/ 1000.0f);
	}
	if (auslenkungY < 0) {
		ausrichtung.y = (map(auslenkungY, 0, (_yMaxWert - _y0Wert), 0, -20000)
				/ 1000.0f);
	} else {
		ausrichtung.y = (map(auslenkungY, 0, (_yMinWert - _y0Wert), 0, 20000)
				/ 1000.0f);
	}
	ausrichtung.z = 0;
	return ausrichtung;
}

