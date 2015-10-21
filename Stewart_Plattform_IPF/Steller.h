/*
 * Steller.h
 *
 *  Created on: 19.10.2015
 *      Author: Ruben Brueckner
 */

#ifndef STELLER_H_
#define STELLER_H_

#include <Arduino.h>
#include <Servo.h>

class Steller: Servo {
public:
	Steller();
	virtual ~Steller();
	void stelle(int angle);
	void attach();
	void detach();
	int getAnalogAngle();
	int getLastAngle();
	void setAngles(int flat, int upright);
	void setPins(int analogPin, int pwmPin);
private:
	int _upright, _flat, _analogPin, _pwmPin, _minAn, _maxAn, _lastAngle;
	void setAnalogLimits();
	boolean _pinSet, _angleSet;
};

#endif /* STELLER_H_ */
