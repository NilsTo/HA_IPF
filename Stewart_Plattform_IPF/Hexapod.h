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


class Hexapod {


public:

	Hexapod(float,float,int,int,int,int,int,int);

	virtual ~Hexapod();

	void AnkerSetzenObenX(float,float,float,float,float,float);

	void AnkerSetzenObenY(float,float,float,float,float,float);

	void AnkerSetzenUntenX(float,float,float,float,float,float);

	void AnkerSetzenUntenY(float,float,float,float,float,float);

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
	};

	arm arme[6];

	// TODO Hier noch neue Array von Klasse Steller hinzufuegen

	Vector calcRotMatrix(Vector, float, float, float);



};

#endif /* HEXAPOD_H_ */
