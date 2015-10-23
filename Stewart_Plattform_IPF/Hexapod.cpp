/*
 * Hexapod.cpp
 *
 *  Created on: 19.10.2015
 *      Author: Nils
 */
#include "Hexapod.h"

Hexapod::Hexapod(float LOA, float LUA, float dhoehe, float baseR, float topR,
		float basewi[6], float topwi[6], float winkel[6], int pwm[6],
		int analog[6], int waagerecht[6], int senkrecht[6]) {
	//Geometrie der a definieren
	for (int i = 0; i < 6; i++) {
		//Armlängen definieren
		a[i].LaengeOberarm = LOA;
		a[i].LaengeUnterarm = LUA;
		//Oberen Anker definieren
		a[i].topVec.x = topR * cos(topwi[i] * DEG_TO_RAD);
		a[i].topVec.y = topR * sin(topwi[i] * DEG_TO_RAD);
		a[i].topVec.z = 0;
		//Unteren Anker definieren
		a[i].baseVec.x = baseR * cos(basewi[i] * DEG_TO_RAD);
		a[i].baseVec.y = baseR * sin(basewi[i] * DEG_TO_RAD);
		a[i].baseVec.z = 0;
		//Lagewinkel definieren
		a[i].beta = (winkel[i] * DEG_TO_RAD);
		//Definieren der Servovariabeln
		a[i].aktor.setPins(analog[i], pwm[i]);
		a[i].aktor.setAngles(waagerecht[i], senkrecht[i]);
		dheight.x = 0.0;
		dheight.y = 0.0;
		dheight.z = dhoehe;
		homeWinkel = 36.0;
	}
}

Hexapod::~Hexapod() {
	// TODO Auto-generated destructor stub
}
/*
 * Fährt den Hexapod in seine Ausgangsposition. UNSAUBER!!
 */
void Hexapod::goHome() {
	for (int i = 0; i < 6; i++) {
		a[i].aktor.stelle(homeWinkel);
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
// Wird eher nicht benötigt!
float Hexapod::calcHomeWinkel(int winkel) {
	float xOxU = (a[winkel].topVec.x - a[winkel].baseVec.x);
	float yOyU = (a[winkel].topVec.y - a[winkel].baseVec.y);
	float h0 = sqrt(
			(a[winkel].LaengeUnterarm * a[winkel].LaengeUnterarm)
					+ (a[winkel].LaengeOberarm * a[winkel].LaengeOberarm)
					- (xOxU * xOxU) - (yOyU * yOyU)) - a[winkel].topVec.z;
	float L0 = 2 * a[winkel].LaengeOberarm * a[winkel].LaengeOberarm;
	float M0 = 2 * a[winkel].LaengeOberarm * xOxU;
	float N0 = 2 * a[winkel].LaengeOberarm * (h0 + a[winkel].topVec.z);
	float a0 = (asin(L0 / sqrt(M0 * M0 + N0 * N0)) - atan2(M0, N0)) * RAD_TO_DEG;
	return a0;
}

/*
 * Ermöglicht das Verfahren der oberen Plattform in anzugebene kartesische Koordinaten und die dazugehörigen Eulerwinkel
 */
bool Hexapod::verfahren(float xx, float yy, float zz, float yawAngle,
		float pitchAngle, float rollAngle) {
//Ortsvektor der Zielkoordinaten
	Vector ziel;
	ziel.x = xx;
	ziel.y = yy;
	ziel.z = zz;
//Umwandeln der Winkel in Rad
	float zRotation = (yawAngle * DEG_TO_RAD);
	float xRotation = (pitchAngle * DEG_TO_RAD);
	float yRotation = (rollAngle * DEG_TO_RAD);
//Berechnung der dynamischen Laenge und des dafuer verantwortlichen Winkels des Stellers
	for (int i = 0; i < 6; i++) {
		Vector matrixErgebnis = calcRotMatrix(a[i].topVec, zRotation, xRotation,
				yRotation);
		Vector q = ziel + matrixErgebnis + dheight;
		Vector l = q - a[i].baseVec;
		a[i].dynLaenge = l.Length();
		//Winkel - Hilfsgrößen
		float L = (a[i].dynLaenge * a[i].dynLaenge)
				- (a[i].LaengeUnterarm * a[i].LaengeUnterarm)
				+ (a[i].LaengeOberarm * a[i].LaengeOberarm);
		float M = 2 * a[i].LaengeOberarm * (q.z - a[i].baseVec.z);   //Änderung
		float N = 2 * a[i].LaengeOberarm
				* (cos(a[i].beta) * (q.x - a[i].baseVec.x) //Änderung
				+ sin(a[i].beta) * (q.y - a[i].baseVec.y)); //Änderung
		//Berechnen des Winkels
		a[i].dynWinkel = (asin(L / sqrt(M * M + N * N)) - atan(N / M))
				* RAD_TO_DEG;
	}
	//Checken, ob Werte erreicht werden koennen.
	for (int i = 0;i<6;i++){
		float wi = a[i].dynWinkel;
		if (wi <0 || wi >90 || isnan(wi) != 0) return false;
	}
	//Ausgabe der Winkel an den Steller - Verfahren der Arme
	//Berechnung des groesten Stellwinkels.
	int pause;
	int deltaWiMax = 1;  //Muss !=0 sein, damit keine Division mit 0 erfolgt.
	for (int i = 0; i < 6; i++) {
		int deltaWi = 0;
		int stellWinkel = int(a[i].dynWinkel + 0.5);
	    bool aktiv = a[i].aktor.attached();
	    if (!aktiv) a[i].aktor.attach();
		deltaWi = a[i].aktor.stelle(stellWinkel);
		if (deltaWi > deltaWiMax) deltaWiMax = deltaWi;
	}
	//Berechnung der max. Zeit für physisches verfahren eines Aktors
	pause = int((deltaWiMax / speed));
	delay(pause);
	return true;
}

