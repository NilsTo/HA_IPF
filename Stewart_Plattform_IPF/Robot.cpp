/*
 *  * Robot.cpp
 * Bisher in sehr grundlegendem Status verblieben. Kommt nicht zur erfolgreichen
 * Anwendung (zur Problematik siehe Doku).
 *
 *  Created on: 25.10.2015
 *      Author: Nils
 */

#include "Robot.h"

Robot::Robot(int pwmpin[6], int analogpin[6], int flat[6], int up[6],
		int anzahlSP) {
	for (int i = 0; i < 6; i++) {
		ra[i].wiSP[anzahlSP];
		ra[i].aktor.setPins(analogpin[i], pwmpin[i]);
		ra[i].aktor.setAngles(flat[i], up[i]);
	}
	_anzSP = 0;
}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}

void Robot::kalibrieren(){
	for (int i = 0;i<6;i++){
		ra[i].aktor.attach();
		ra[i].aktor.stelle(3); //TODO andere Werte
		delay(500);
		int minAn = analogRead(ra[i].aktor.getAnalogPin());
		ra[i].aktor.stelle(87); //TODO andere Werte
		delay(500);
		int maxAn = analogRead(ra[i].aktor.getAnalogPin());
		ra[i].aktor.setAnalogLimits(minAn,maxAn);
		ra[i].aktor.stelle(36);
		delay(500);
		ra[i].aktor.detach();
	}
}

void Robot::speichern() {
	for (int i = 0; i < 6; i++) {
		ra[i].wiSP[_anzSP] = ra[i].aktor.getAnalogAngle();
	}
	Serial.println("Gespeichert"); // TODO Umstellung auf LCD
	_anzSP++;
	if (_anzSP > 9)
		_anzSP = 0;  // Unsauber - aber .lenght gibt nur bytes die vorhanden sind zurück
}

void Robot::manuell(){
	for (int i = 0; i<6;i++){
		ra[i].aktor.detach();
	}
}

void Robot::ablauf() {
	for (int i = 0; i <= _anzSP; i++){
		for (int k = 0;k<6;k++){
			ra[k].aktor.attach();
			ra[k].aktor.stelle(ra[k].wiSP[i]);
		}
		delay(1000);
	}

}
