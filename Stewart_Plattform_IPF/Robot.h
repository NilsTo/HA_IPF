/*
 * Robot.h
 *
 *  Created on: 25.10.2015
 *      Author: Nils
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "Arduino.h"
#include "Steller.h"

class Robot {
public:
	Robot(int pwmpin[6], int analogpin[6], int flat[6], int up[6], int anzahlSP);
	virtual ~Robot();
	void speichern();
	void ablauf();
	void manuell();
	void kalibrieren();

private:

	int _anzSP;

	struct roboarm {
		int wiSP[];
		Steller aktor;
	};

	roboarm ra[6];

};

#endif /* ROBOT_H_ */
