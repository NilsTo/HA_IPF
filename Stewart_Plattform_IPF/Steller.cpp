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
		this->Servo::detach();
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
void Steller::setAnalogLimits(int minAn, int maxAn) {
	// Poti-Wert bei waagerechter Position
	this->_minAn = minAn;
	// Poti-Wert bei senkrechter Position
	this->_maxAn = maxAn;

}

/**
 *  Beginnt das Schreiben eines PWM-Signals auf Servo-PWM-Pin.
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
		 * Es wäre möglich, ein initiales Schreiben auf den Servo zu unterdrücken:
		 *
		 * Quelle: (http://stackoverflow.com/questions/26695670/attach-arduino-servo-without-moving)
		 * // ANFANG ZITAT
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
		 * // ENDE ZITAT
		 *
		 * Von der Verwendung der vorgestellten Methode wurde abgesehen, da dies in den Augen des Autors
		 * nicht notwendig ist. Stattdessen fahren die sechs Servos zu Beginn nacheinander (bei attach())
		 * an eine Initialposition.
		 */

		this->stelle(36);
		// Verzoegerung, da aktuelle Position nicht bekannt ist und auch im
		// nicht definierten Bereich liegen kann.
		delay(500);
		this->Servo::attach(_pwmPin);

	}
}

/**
 *  Vereinfacht das Einstellen eines Winkels am Servo, gibt als Bestaetigung
 *  die Winkelaenderung zurueck.
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
				"Der eingestellte Winkel liegt nicht im definierten Bereich.");
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
				"Die Grenzwinkel sind nicht bekannt. Setze diese mit Steller::setAnalogLimits().");
		return 1023;
	}
}

/**
 * gibt zuletzt geschriebenen Wert (ohne Mapping) zurueck,
 * der am Ende von ::stelle jeweils in das Objekt geschrieben wird.
 */

int Steller::getLastAngle() {
	return this->_lastAngle;
}

int Steller::getAnalogPin(){
	return this->_analogPin;
}
