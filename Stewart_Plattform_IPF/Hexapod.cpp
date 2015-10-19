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
			arme[i].WinkelAusrichtung = W1;
			break;
		case 1:
			arme[i].WinkelAusrichtung = W2;
			break;
		case 2:
			arme[i].WinkelAusrichtung = W3;
			break;
		case 3:
			arme[i].WinkelAusrichtung = W4;
			break;
		case 4:
			arme[i].WinkelAusrichtung = W5;
			break;
		case 5:
			arme[i].WinkelAusrichtung = W6;
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
	c.x = (cos(yaw)*cos(pitch)*b.x) +
	c.y = (sin(yaw)*cos(pitch)*b.y) +
	c.z = ((-sin(pitch))*b.z) +
return c;
}

Hexapod::verfahren(float xx,float yy,float zz, float yawAngel, float pitchAngel, float rollAngel) {

}

