/*
 * Hexapod.cpp
 *
 *  Created on: 19.10.2015
 *      Author: Nils
 */
#include "Hexapod.h"

Hexapod::Hexapod(float LOA, float LUA,float ankerUX[6], float ankerUY[6], float ankerUZ[6],
		float ankerOX[6], float ankerOY[6], float ankerOZ[6], int winkel[6],
		int pwm[6], int analog[6], int waagerecht[6], int senkrecht[6]) {
	//Geometrie der Arme definieren
	for (int i = 0; i < 6; i++) {
		//Armlängen definieren
		arme[i].LaengeOberarm = LOA;
		arme[i].LaengeUnterarm = LUA;
		//Oberen Anker definieren
		arme[i].AnkerOben.x = ankerOX[i];
		arme[i].AnkerOben.y = ankerOY[i];
		arme[i].AnkerOben.z = ankerOZ[i];
		//Unteren Anker definieren
		arme[i].AnkerUnten.x = ankerUX[i];
		arme[i].AnkerUnten.y = ankerUY[i];
		arme[i].AnkerUnten.z = ankerUZ[i];
		//Lagewinkel definieren
		arme[i].WinkelAusrichtung = (winkel[i] * DEG2RAD);
		//Definieren der Servovariabeln
		arme[i].aktor.setPins(analog[i], pwm[i]);
		arme[i].aktor.setAngles(waagerecht[i], senkrecht[i]);
		//Berechnen des neutralen Winkels, mit dem 5 Servo, da dieser ein beta von 0 hat.
		//homeWinkel = calcHomeWinkel(4);
		homeWinkel = 45.0;
	}
}

Hexapod::~Hexapod() {
	// TODO Auto-generated destructor stub
}
/*
 * Fährt den Hexapod in seine Ausgangsposition.
 */
void Hexapod::goHome() {
	for (int i = 0; i < 6; i++) {
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

float Hexapod::calcHomeWinkel(int winkel) {
	float xOxU = (arme[winkel].AnkerOben.x - arme[winkel].AnkerUnten.x);
	float yOyU = (arme[winkel].AnkerOben.y - arme[winkel].AnkerUnten.y);
	float h0 = sqrt(
			(arme[winkel].LaengeUnterarm * arme[winkel].LaengeUnterarm)
					+ (arme[winkel].LaengeOberarm * arme[winkel].LaengeOberarm)
					- (xOxU * xOxU) - (yOyU * yOyU)) - arme[winkel].AnkerOben.z;
	float L0 = 2 * arme[winkel].LaengeOberarm * arme[winkel].LaengeOberarm;
	float M0 = 2 * arme[winkel].LaengeOberarm * xOxU;
	float N0 = 2 * arme[winkel].LaengeOberarm * (h0 + arme[winkel].AnkerOben.z);
	double a0 = (asin(L0/sqrt(M0*M0+N0*N0)) - atan2(M0, N0)) * RAD2DEG;
	return a0;
}

/*
 * Ermöglicht das Verfahren der oberen Plattform in anzugebene kartesische Koordinaten und die dazugehörigen Eulerwinkel
 */
void Hexapod::verfahren(float xx, float yy, float zz, float yawAngle,
		float pitchAngle, float rollAngle) {
	Serial.print("Eingabe: ");
	Serial.println(zz);
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
		Vector hoehe;
		hoehe.z = 115;
		Vector qErgebnis = ziel + matrixErgebnis + hoehe;
		Vector lErgebnis = qErgebnis - arme[i].AnkerUnten;
		 arme[i].dynLaenge = lErgebnis.Length();
		 Serial.println("Länge =");
		 Serial.print(arme[i].dynLaenge);
		//Winkel - Hilfsgrößen
		float L = (arme[i].dynLaenge * arme[i].dynLaenge)
				- ((arme[i].LaengeUnterarm * arme[i].LaengeUnterarm)
				- (arme[i].LaengeOberarm * arme[i].LaengeOberarm));
		float M = 2 * arme[i].LaengeOberarm
				* (qErgebnis.z - arme[i].AnkerUnten.z);   //Änderung
		float N = 2 * arme[i].LaengeOberarm
				* (cos(arme[i].WinkelAusrichtung)
					* (qErgebnis.x - arme[i].AnkerUnten.x)  	//Änderung
						+ sin(arme[i].WinkelAusrichtung)
								* (qErgebnis.y - arme[i].AnkerUnten.y)); //Änderung
		//Berechnen des Winkels
		arme[i].dynWinkel = (asin(L / sqrt((M * M) + (N * N))) - atan2(N, M))
				* RAD2DEG;
		Serial.print("Winkel =");
		Serial.print(arme[i].dynWinkel);

	}
	Serial.println("Ende");
	for (int i = 0; i < 6; i++) {
		//int winkel = int(arme[i].dynWinkel) - int(homeWinkel);
		//arme[i].aktor.stelle(winkel);
	}
}

