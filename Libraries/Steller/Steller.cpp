/*
 *  Steller.cpp
 *	Beerbt die Klasse Servo und stattet ein Servo mit Informationen und
 *	Funktionen aus, sodass nur noch ein 90-Grad-Bereich genutzt wird.
 *
 *	Stellt des Weiteren Funktionen zur Verwendung des integrierten Potentionmeters bereit.
 *
 *  Created on: 18.10.2015
 *  Author: Ruben Brueckner
 */

#include "Arduino.h"
#include <Steller.h>
#include "Servo.h"

Steller::Steller(String name, int flat, int upright, int pulsePin,
		int potiPin, boolean clockwise) {
	this->_flat = flat; 		// Arduino-Servo-PWM @ 0deg
	this->_upright = upright;	// Arduino-Servo-PWM @ 90deg
	this->_pulsePin = pulsePin;	// PWM-Pin
	this->_potiPin = potiPin;	// Potentionmeter-Input (A)0~(A)N
	//Servo::Servo(); // Da kein Argument, kein expliziter Aufruf der beerbten Klasse
}

/*
 * Die Funktion writenNDS schreibt nur winkel im festgelegten bereich
 * NOT TESTED YET!
 */
void Steller::writeNDS(int angle) {
	if (angle >= 0 && angle < 91) { // Verhindern, dass ungültige Werte gemappt werden.
		angle = map(angle, 0, 90, _flat, _upright);
		this->write(angle);
	} else {
		Serial.print("ERROR in NINETYDEGSERVO.CPP: ANGLE OUT OF RANGE");
	}
}

/*
 * Die Funktion gibt den zuletzt geschriebenen Winkel zurueck
 */

int Steller::readNDS() {
	return map(this->read(), 0, 180, this->_flat, this->_upright);
}

/*
 * Die Funktion checkAnalogAngle prueft, ob die Servo-Position im zulässigen Bereich liegt
 * - notwendig für die Einspeicherung von manuell eingestellten Fahrpositionen
 *
 * Hierfür müsste zunächst festgestellt werden, welche Analog-Range jeweils iO ist... //TODO
 */
boolean Steller::analogAngleInRange() {
	return false; // TODO
}

