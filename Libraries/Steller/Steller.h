/**
 *  Steller.h
 *
 *  Created on 18.10.15
 *  Author: Ruben Brueckner
 */
#ifndef LIBRARIES_STELLER_STELLER_H_
#define LIBRARIES_STELLER_STELLER_H_

#include <Arduino.h>
#include <Servo.h>

class Steller : public Servo
{
  public:
    Steller(String name, int flat, int upwards, int pulsePin, int potiPin);
    void writeNDS(int angle);
    boolean analogAngleInRange();
    int readNDS();
  private:
    int _flat, _upright, _pulsePin, _potiPin;
    boolean clockwise;

};






#endif /* LIBRARIES_STELLER_STELLER_H_ */
