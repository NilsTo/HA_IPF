/*
 * Hexapod.cpp
 *
 *  Created on: 19.10.2015
 *      Author: Nils
 */
#include "Hexapod.h"

Hexapod::Hexapod(float LOA, float LUA, int W1, int W2, int W3, int W4, int W5,
		int W6) {
	for (int i = 0; i < 6; i++) {
		//Definieren der Laengen
		arme[i].LaengeOberarm = LOA;
		arme[i].LaengeUnterarm = LUA;
		//Auswahl des korrekten Winkels
		switch (i) {
		case 0:
			arme[i].WinkelAusrichtung = (W1 * DEG2RAD);
			break;
		case 1:
			arme[i].WinkelAusrichtung = (W2 * DEG2RAD);
			break;
		case 2:
			arme[i].WinkelAusrichtung = (W3 * DEG2RAD);
			break;
		case 3:
			arme[i].WinkelAusrichtung = (W4 * DEG2RAD);
			break;
		case 4:
			arme[i].WinkelAusrichtung = (W5 * DEG2RAD);
			break;
		case 5:
			arme[i].WinkelAusrichtung = (W6 * DEG2RAD);
			break;
		}
	}
}

Hexapod::~Hexapod() {
	// TODO Auto-generated destructor stub
}
void Hexapod::ankerSetzenObenX(float xo1, float xo2, float xo3, float xo4,
		float xo5, float xo6) {
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 0:
			arme[i].AnkerOben.x = xo1;
			break;
		case 1:
			arme[i].AnkerOben.x = xo2;
			break;
		case 2:
			arme[i].AnkerOben.x = xo3;
			break;
		case 3:
			arme[i].AnkerOben.x = xo4;
			break;
		case 4:
			arme[i].AnkerOben.x = xo5;
			break;
		case 5:
			arme[i].AnkerOben.x = xo6;
			break;
		}
	}
}

void Hexapod::ankerSetzenObenY(float yo1, float yo2, float yo3, float yo4,

float yo5, float yo6) {
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 0:
			arme[i].AnkerOben.y = yo1;
			break;
		case 1:
			arme[i].AnkerOben.y = yo2;
			break;
		case 2:
			arme[i].AnkerOben.y = yo3;
			break;
		case 3:
			arme[i].AnkerOben.y = yo4;
			break;
		case 4:
			arme[i].AnkerOben.y = yo5;
			break;
		case 5:
			arme[i].AnkerOben.y = yo6;
			break;
		}
	}
}

void Hexapod::ankerSetzenObenZ(float zo1, float zo2, float zo3, float zo4,
		float zo5, float zo6) {
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 0:
			arme[i].AnkerOben.z = zo1;
			break;
		case 1:
			arme[i].AnkerOben.z = zo2;
			break;
		case 2:
			arme[i].AnkerOben.z = zo3;
			break;
		case 3:
			arme[i].AnkerOben.z = zo4;
			break;
		case 4:
			arme[i].AnkerOben.z = zo5;
			break;
		case 5:
			arme[i].AnkerOben.z = zo6;
			break;
		}
	}
}

void Hexapod::ankerSetzenUntenX(float xu1, float xu2, float xu3, float xu4,
		float xu5, float xu6) {
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 0:
			arme[i].AnkerUnten.x = xu1;
			break;
		case 1:
			arme[i].AnkerUnten.x = xu2;
			break;
		case 2:
			arme[i].AnkerUnten.x = xu3;
			break;
		case 3:
			arme[i].AnkerUnten.x = xu4;
			break;
		case 4:
			arme[i].AnkerUnten.x = xu5;
			break;
		case 5:
			arme[i].AnkerUnten.x = xu6;
			break;
		}
	}
}

void Hexapod::ankerSetzenUntenY(float yu1, float yu2, float yu3, float yu4,
		float yu5, float yu6) {
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 0:
			arme[i].AnkerUnten.y = yu1;
			break;
		case 1:
			arme[i].AnkerUnten.y = yu2;
			break;
		case 2:
			arme[i].AnkerUnten.y = yu3;
			break;
		case 3:
			arme[i].AnkerUnten.y = yu4;
			break;
		case 4:
			arme[i].AnkerUnten.y = yu5;
			break;
		case 5:
			arme[i].AnkerUnten.y = yu6;
			break;
		}
	}
}

void Hexapod::ankerSetzenUntenZ(float zu1, float zu2, float zu3, float zu4,
		float zu5, float zu6) {
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 0:
			arme[i].AnkerUnten.z = zu1;
			break;
		case 1:
			arme[i].AnkerUnten.z = zu2;
			break;
		case 2:
			arme[i].AnkerUnten.z = zu3;
			break;
		case 3:
			arme[i].AnkerUnten.z = zu4;
			break;
		case 4:
			arme[i].AnkerUnten.z = zu5;
			break;
		case 5:
			arme[i].AnkerUnten.z = zu6;
			break;
		}
	}
}

void Hexapod::erstelleMotor(int name, int pwmPin, int analogPin, int waagerecht,
		int senkrecht) {
	switch (name) {
	case 1:
		arme[0].aktor.setPins(analogPin, pwmPin);
		arme[0].aktor.setAngles(waagerecht, senkrecht);
		break;
	case 2:
		arme[1].aktor.setPins(analogPin, pwmPin);
		arme[1].aktor.setAngles(waagerecht, senkrecht);
		break;
	case 3:
		arme[2].aktor.setPins(analogPin, pwmPin);
		arme[2].aktor.setAngles(waagerecht, senkrecht);
		break;
	case 4:
		arme[3].aktor.setPins(analogPin, pwmPin);
		arme[3].aktor.setAngles(waagerecht, senkrecht);
		break;
	case 5:
		arme[4].aktor.setPins(analogPin, pwmPin);
		arme[4].aktor.setAngles(waagerecht, senkrecht);
		break;
	case 6:
		arme[5].aktor.setPins(analogPin, pwmPin);
		arme[5].aktor.setAngles(waagerecht, senkrecht);
		break;
	}
}

void Hexapod::goHome() {
	for (int i = 0;i<6;i++){
		arme[i].aktor.stelle(45);
	}
}

/*
 * Methode berechnet den Vektor aus Rotationsmatrix u. Vektor des oberen Ankerpunktes.
 */
Vector Hexapod::calcRotMatrix(Vector b, float yaw, float pitch, float roll) {
	Vector c;
	c.x = (cos(yaw) * cos(pitch) * b.x)
			+ (-sin(yaw) * cos(roll) + cos(yaw) * sin(pitch) * sin(roll)) * b.y
			+ (sin(yaw) * sin(roll) + cos(yaw) * sin(pitch) * cos(roll)) * b.z;
	c.y = (sin(yaw) * cos(pitch) * b.x)
			+ (cos(yaw) * cos(roll) + sin(yaw) * sin(pitch) * sin(roll)) * b.y
			+ (-cos(yaw) * sin(roll) + sin(yaw) * sin(pitch) * cos(roll)) * b.z;
	c.z = ((-sin(pitch)) * b.x) + cos(pitch) * sin(roll) * b.y
			+ cos(pitch) * cos(roll) * b.z;
	return c;
}
/*
 * Ermöglicht das Verfahren der oberen Plattform in anzugebene kartesische Koordinaten und die dazugehörigen Eulerwinkel
 */
void Hexapod::verfahren(float xx, float yy, float zz, float yawAngel,
		float pitchAngel, float rollAngel) {
	//Ortsvektor der Zielkoordinaten
	Vector ziel;
	ziel.x = xx;
	ziel.y = yy;
	ziel.z = zz;
	//Umwandeln der Winkel in Rad
	float yAngel = (yawAngel * DEG2RAD);
	float pAngel = (pitchAngel * DEG2RAD);
	float rAngel = (rollAngel * DEG2RAD);
	//Berechnung der dynamischen Laenge und des dafuer verantwortlichen Winkels des Stellers
	for (int i = 0; i < 6; i++) {
		Vector matrixErgebnis = calcRotMatrix(arme[i].AnkerOben, yAngel, pAngel,
				rAngel);
		arme[i].dynLaenge = ziel + matrixErgebnis - arme[i].AnkerUnten;
		//Winkel - Hilfsgrößen
		float L = (arme[i].dynLaenge * arme[i].dynLaenge)
				- (arme[i].LaengeUnterarm * arme[i].LaengeUnterarm)
				+ (arme[i].LaengeOberarm * arme[i].LaengeOberarm);
		float M = 2 * arme[i].LaengeOberarm
				* (arme[i].AnkerOben.z - arme[i].AnkerUnten.z);
		float N = 2 * arme[i].LaengeOberarm
				* (cos(arme[i].WinkelAusrichtung)
						* (arme[i].AnkerOben.x - arme[i].AnkerUnten.x)
						+ sin(arme[i].WinkelAusrichtung)
								* (arme[i].AnkerOben.y - arme[i].AnkerUnten.y));
		//Berechnen des Winkels
		arme[i].dynWinkel = (asin(L / sqrt(M * M + N * N)) - atan(N / M))
				* RAD2DEG;
	}
	for (int i = 0;i<6;i++){
		int winkel = int(arme[i].dynWinkel);
		arme[i].aktor.stelle(winkel);
	}
}

