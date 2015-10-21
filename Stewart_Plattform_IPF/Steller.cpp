/*
 * Steller.cpp
 *
 *  Created on: 19.10.2015
 *      Author: Ruben Brueckner
 */

#include "Steller.h"

// by setting ALWAYS_ATTACHED true, one is not able to
// manually manipulate the Servos during operation anymore
#define ALWAYS_ATTACHED (false)  // Konzept nicht ganz durchdacht?!

/**
 *  Erstellt neuen Steller, eine Subklasse von Servo.
 *  Es m�ssen mindestens Informationen �ber die PIN-Belegung und
 *  die zu den Winkel geh�renden Servo.h-Winkel angegeben werden.
 */
Steller::Steller() {
}

Steller::~Steller() {
	// Detach Servo if not in use anymore.
	if (ALWAYS_ATTACHED) {
		this->detach();
	}
}
/**
 * int flat, int upright sind die Grenzen, die im Projekt angefahren werden duerfen
 */
void Steller::setAngles(int flat, int upright) {
	this->_upright = upright;
	this->_flat = flat;
	this->_angleSet = true;
}

/**
 *  anzusteuernder PWM-Pin und
 *  auszulesender analog-Pin
 */
void Steller::setPins(int analogPin, int pwmPin) {
	this->_analogPin = analogPin;
	this->_pwmPin = pwmPin;
	this->_pinSet = true;
}

/**
 *  Private Methode zum Ermitteln der Limits.
 *  Ein Aufrufen d�rfte nur durch eine Initialisierungsmethode
 *  laufen, wenn es also nicht stoert o.ae.
 */
void Steller::setAnalogLimits() {
	this->stelle(0);
	this->_minAn = analogRead(_analogPin);
	// Serial.Print(_minAn);
	this->stelle(90);
	this->_maxAn = analogRead(_analogPin);
	// Serial.Print(_maxAn);
}

/**
 *  schlie�t den Servo an.
 */
void Steller::attach() {
	if (_angleSet && _pinSet) {
		this->Servo::attach(_pwmPin);
		this->stelle(90);	// initiale Fahrt zur Spitze
		delay(500);			// nacheinander
	}
}

void Steller::detach() {
	this->Servo::detach();
}

/**
 *  Vereinfacht das Einstellen eines Winkels am Servo
 */
void Steller::stelle(int angle) {
	if (angle >= 0 && angle < 91) {
		int setpoint = map(angle, 0, 90, _flat, _upright);
		// Ausgabe des Servosignals
		this->Servo::write(setpoint);
		this->_lastAngle = angle;
		//wurde entfernt, weil Fehler!
		Serial.println(setpoint);
		Serial.println("upright");
		Serial.println(_upright);
		Serial.println("flat");
		Serial.println(_flat);
		//delay(200); // TODO Wie lang muss der Servo wirklich angesteuert werden?

	} else {
		Serial.println(
				"Angle input error. Steller::stelle did not recieve a correct angle.");
	}
}

/**
 *  Gibt den aufgrund der Potentiometer-Spannung ermittelten Winkel des Servohorns zurueck.
 *  Sollten die Grenzen noch nicht gesetzt sein, gibt sie 1023 zurueck.
 */
int Steller::getAnalogAngle() {
	if (_minAn != 0 && _maxAn != 0) {
		int angle = map(analogRead(_analogPin), _minAn, _maxAn, 0, 90);
		return angle;
	} else {
		Serial.println(
				"Limits are not known yet. Steller::setAnalogLimits() may be a good idea.");
		return 1023;
	}
}

/**
 * gibt zuletzt geschriebenen Wert (ohne Mapping) zurueck,
 * der am Ende von ::stelle jeweils in das Objekt geschrieben wird.
 */

int Steller::getLastAngle() {
	return _lastAngle;
}
