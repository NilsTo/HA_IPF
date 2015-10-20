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

	Hexapod(float,float,int,int,int,int,int,int);

	virtual ~Hexapod();

	void ankerSetzenObenX(float,float,float,float,float,float);

	void ankerSetzenObenY(float,float,float,float,float,float);

	void ankerSetzenObenZ(float,float,float,float,float,float);

	void ankerSetzenUntenX(float,float,float,float,float,float);

	void ankerSetzenUntenY(float,float,float,float,float,float);

	void ankerSetzenUntenZ(float,float,float,float,float,float);

	void erstelleMotor(int,int,int,int,int);

	void createSteller();

	void goHome();

	void verfahren(float,float,float,float,float,float);

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

	Vector calcRotMatrix(Vector, float, float, float);



};

#endif /* HEXAPOD_H_ */
