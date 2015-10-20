/*
 * Hexapod.cpp
 *
 *  Created on: 19.10.2015
 *      Author: Nils
 */
#include "Hexapod.h"

Hexapod::Hexapod(float ankerUX[6], float ankerUY[6], float ankerUZ[6],
		float ankerOX[6], float ankerOY[6], float ankerOZ[6], int winkel[6],
		int pwm[6], int analog[6], int waagerecht[6], int senkrecht[6]){
	//Geometrie der Arme definieren
	for (int i = 0;i<6;i++) {
		//Oberen Anker definieren
		arme[i].AnkerOben.x = ankerOX[i];
		arme[i].AnkerOben.y = ankerOY[i];
		arme[i].AnkerOben.z = ankerOZ[i];
		//Unteren Anker definieren
		arme[i].AnkerUnten.x = ankerUX[i];
		arme[i].AnkerUnten.y = ankerUY[i];
		arme[i].AnkerUnten.z = ankerUZ[i];
		//Lagewinkel definieren
		arme[i].WinkelAusrichtung = winkel[i];
		//Definieren der Servovariabeln
		arme[i].aktor.setPins(analog[i],pwm[i]);
		arme[i].aktor.setAngles(waagerecht[i],senkrecht[i]);
	}
}

Hexapod::~Hexapod() {
	// TODO Auto-generated destructor stub
}
/*
 * Fährt den Hexapod in seine Ausgangsposition.
 */
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
void Hexapod::verfahren(float xx, float yy, float zz, float yawAngle,
		float pitchAngle, float rollAngle) {
	//Ortsvektor der Zielkoordinaten
	Vector ziel;
	ziel.x = xx;
	ziel.y = yy;
	ziel.z = zz;
	//Umwandeln der Winkel in Rad
	float yAngle = (yawAngle * DEG2RAD);
	float pAngle = (pitchAngle * DEG2RAD);
	float rAngle = (rollAngle * DEG2RAD);
	//Berechnung der dynamischen Laenge und des dafuer verantwortlichen Winkels des Stellers
	for (int i = 0; i < 6; i++) {
		Vector matrixErgebnis = calcRotMatrix(arme[i].AnkerOben, yAngle, pAngle,
				rAngle);
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
		arme[i].dynWinkel = (asin(L / sqrt(M * M + N * N)) - atan2(N , M))
				* RAD2DEG;
	}
	for (int i = 0;i<6;i++){
		int winkel = int(arme[i].dynWinkel);
		arme[i].aktor.stelle(winkel);
	}
}

