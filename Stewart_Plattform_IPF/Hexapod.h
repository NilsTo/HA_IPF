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

	Hexapod(float LOA,float LUA,float ankerUX[6], float ankerUY[6], float ankerUZ[6],
			float ankerOX[6], float ankerOY[6], float ankerOZ[6], int winkel[6],
			int pwm[6], int analog[6], int waagerecht[6], int senkrecht[6]);

	virtual ~Hexapod();

	void goHome();

	void verfahren(float, float, float, float, float, float);

	float calcHomeWinkel(int);

private:

	/*
	 * Dateityp Arm fuer die Spaetere Zusamenfassung geometrischer Merkmale.
	 */
	struct arm {
		Vector AnkerUnten;
		Vector AnkerOben;
		float LaengeOberarm;
		float LaengeUnterarm;
		int WinkelAusrichtung;
		float dynLaenge;
		float dynWinkel;
		Steller aktor;
	};
// Array zur Aufnahme der 6 Arme an einer Plattform
	arm arme[6];

//Wert des neutralWinkels, wird im constructor berechnet
	float homeWinkel;

	Vector calcRotMatrix(Vector, float, float, float);
	/*
	 * Funktion, die den Normalwinkel berechnet, ben�tigt als int, bei welchem Servo beta=0
	 */


};

#endif /* HEXAPOD_H_ */
