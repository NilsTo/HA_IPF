/*
 * Hexapod.cpp
 *
 *  Created on: 19.10.2015
 *      Author: Nils
 */
#include "Hexapod.h"

Hexapod::Hexapod(float x_u, float y_u, float z_u, float x_o, float y_o,
		float z_o, float LOA, float LUA, int W1, int W2, int W3, int W4, int W5,
		int W6) {
	for (int i = 0; i < 6; i++) {
		//Vektor des unteren Befestigungspunkts
		arme[i].AnkerUnten.x = x_u;
		arme[i].AnkerUnten.y = y_u;
		arme[i].AnkerUnten.z = z_u;
		//Vektor des oberen Befestigungspunktes
		arme[i].AnkerOben.x = x_o;
		arme[i].AnkerOben.x = x_o;
		arme[i].AnkerOben.x = x_o;
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

Hexapod::verfahren(float xx, float yy, float zz, float yawAngel,
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
	//Berechnung der dynamischen Laenge und des dafür verantwortlichen Winkels des Stellers
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
		arme[i].dynWinkel = asin(L/sqrt(M*M+N*N)) - atan(N/M);
	}
	// TODO Verfahren der Servos an Position
}

