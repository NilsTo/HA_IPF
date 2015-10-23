/*
 * Hexapod.h
 *
 *  Created on: 19.10.2015
 *      Author: Nils
 */
#ifndef HEXAPOD_H_
#define HEXAPOD_H_

#define DEG2RAD      (PI/180.0f)
#define RAD2DEG      (180.0f/PI)

#include "Arduino.h"
#include "Vector.h"
#include "Steller.h"

class Hexapod {

public:

	Hexapod(float LOA, float LUA,float dhoehe, float baseR, float topR, float basewi[6],
			float topwi[6], float winkel[6], int pwm[6], int analog[6],
			int waagerecht[6], int senkrecht[6]);

	virtual ~Hexapod();

	void goHome();

	bool verfahren(float, float, float, float, float, float);

	float calcHomeWinkel(int);

private:

	/*
	 * Dateityp Arm fuer die Spaetere Zusamenfassung geometrischer Merkmale.
	 */
	struct arm {
		Vector baseVec;
		Vector topVec;
		float LaengeOberarm;
		float LaengeUnterarm;
		float beta;
		float dynLaenge;
		float dynWinkel;
		Steller aktor;
	};
// Array zur Aufnahme der 6 Arme an einer Plattform
	arm a[6];

//Wert des neutralWinkels, wird im constructor berechnet
	float homeWinkel;
	Vector dheight;

	Vector calcRotMatrix(Vector, float, float, float);
	/*
	 * Funktion, die den Normalwinkel berechnet, benötigt als int, bei welchem Servo beta=0
	 */

};

#endif /* HEXAPOD_H_ */
