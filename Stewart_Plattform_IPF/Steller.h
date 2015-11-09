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

#define speed 0.2727272727f   //Geschwindigkeit eines Servos in [Grad/ms]

// oeffentliche Vererbung wurde notwendig, da sonst ein Servo::detach() nicht funktionierte bzw.
// als "weiterleitende Klasse" nicht imt Stil (methode(){this->Mutterklasse::Methode();}) 
// funktionierte

class Steller: public Servo {
public:
	Steller();
	virtual ~Steller();
	int stelle(int angle);
	void attach();
	void detach();
	int getAnalogAngle();
	int getLastAngle();
	bool aktiv();
	void setAngles(int flat, int upright);
	void setPins(int analogPin, int pwmPin);
	void setAnalogLimits(int minAn, int maxAn);
	int getAnalogPin();
private:
	int _upright, _flat, _analogPin, _pwmPin, _minAn, _maxAn, _lastAngle;
	boolean _pinSet, _angleSet;
};

#endif /* STELLER_H_ */
