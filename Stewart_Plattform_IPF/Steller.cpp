/*
 * Steller.cpp
 *
 *  Created on: 19.10.2015
 *      Author: Ruben Brueckner
 */

#include "Steller.h"
/**
 *  Erstellt neuen Steller, eine Subklasse von Servo.
 *  Es müssen mindestens Informationen über die PIN-Belegung und
 *  die zu den Winkel gehörenden Servo.h-Winkel angegeben werden.
 */
Steller::Steller() {
}

Steller::~Steller() {
	// Detach Servo if not in use anymore.
	if (this->attached())
		this->detach();
}
/**
 * int flat, int upright sind die Grenzen,
 * die im Projekt angefahren werden duerfen
 */
void Steller::setAngles(int flat, int upright) {
	this->_upright = upright;
	this->_flat = flat;
	this->_angleSet = true;
}

/**
 *  Setter f. anzusteuernder PWM-Pin und
 *  auszulesender analog-Pin
 */
void Steller::setPins(int analogPin, int pwmPin) {
	this->_analogPin = analogPin;
	this->_pwmPin = pwmPin;
	this->_pinSet = true;
}

/**
 *  Private Methode zum Ermitteln der Limits.
 *  Ein Aufrufen dürfte nur durch eine Initialisierungsmethode
 *  laufen, wenn es also nicht stoert o.ae.
 *
 *  Wird im Zusammenhang mit Auslesen der Potis notwendig.
 */
void Steller::setAnalogLimits() {
	// Poti-Wert bei waagerechter Position
	this->stelle(3);
	delay(500);
	this->_minAn = analogRead(_analogPin);
	// Poti-Wert bei senkrechter Position
	this->stelle(87);
	delay(500);
	this->_maxAn = analogRead(_analogPin);
}

/**
 *  Beginnt das Schreiben eines PWM-Signals auf Servo-PWM-Pin.
 *  Wird vorher auf 90° gesetzt
 */
void Steller::attach() {
	// Anschluss des Servos ist nur nach Definition der
	// Steller-Eigenschaften (zwei Winkel, zwei Pins) zulässig
	if (_angleSet && _pinSet) {

		/*
		 * optional: in senkrechte Position fahren
		 * Delay wird zwischen den einzelnen Servos abgewartet.
		 * wenn das Verhalten als gewünscht angesehen wird,
		 * ist eine Organisation & ein gemeinsamer delay aller
		 * Servos durch die übergeordnete Methode notwendig.
		 *
		 *
		 * Es ist möglich, ein initiales Schreiben auf den Servo zu unterdrücken:
		 *
		 * Quelle: (http://stackoverflow.com/questions/26695670/attach-arduino-servo-without-moving)
		 *
		 * Thanks to djUniversal's answer, I got it working so that the servo doesn't move when attached.
		 * In case anyone else is looking to do the same, all I did was go into ServoTimer2.cpp and comment
		 * out the first 3 lines of the initISR method:
		 *
		 *static void initISR()
		 *{
		 *    for(uint8_t i=1; i <= NBR_CHANNELS; i++) {  // channels start from 1
		 *        writeChan(i, DEFAULT_PULSE_WIDTH);  // store default values
		 *    }
		 *
		 */

		this->stelle(90);
		delay(500);
		this->Servo::attach(_pwmPin);

	}
}

void Steller::detach() {
	this->Servo::detach();
}

/**
 *  Vereinfacht das Einstellen eines Winkels am Servo
 */
int Steller::stelle(int angle) {
	int deltaAngle;
	if (angle >= 0 && angle < 91) {
		int setpoint = map(angle, 0, 90, _flat, _upright);
		// Ausgabe des Servosignals
		deltaAngle = abs(angle - _lastAngle);
		this->Servo::write(setpoint);
		this->_lastAngle = angle;
		return deltaAngle;
	} else {
		Serial.println(
				"Angle input error. Steller::stelle did not recieve a correct angle.");
		return 90;
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
