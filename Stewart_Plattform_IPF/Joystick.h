/*
 * Joystick.h
 *
 *  Created on: 21.10.2015
 *      Author: Nils
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "Arduino.h"
#include "Vector.h"

class Joystick {
public:
	Joystick(int xMinWert,int xMaxWert,int yMinWert,int yMaxWert,int xAxPin,int yAxPin);
	virtual ~Joystick();
	Vector bewegung(int modus);
	Vector ausrichtung();
	void kalibrieren();

private:
	int _x0Wert;
	int _xMinWert;
	int _xMaxWert;
	int _y0Wert;
	int _yMinWert;
	int _yMaxWert;
	int _xAxPin;
	int _yAxPin;

	int	geglaettet(int eingang);
};

#endif /* JOYSTICK_H_ */
