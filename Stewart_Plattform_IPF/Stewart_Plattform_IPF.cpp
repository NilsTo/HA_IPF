// Do not remove the include below
#include "Stewart_Plattform_IPF.h"
#include "Hexapod.h"
#include "Arduino.h"

// benannt nach Etikettierung
float basex[6] = { -86.56, -47.3, 47.3, 86.56, 39.3, -39.3 };
float basey[6] = { 4.66, 72.64, 72.64, 4.66, -77.3, -77.3 };
float basez[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
float topx[6] = { -58.7, -51.7, 51.7, 58.7, 7, -7 };
float topy[6] = { 25.8, 37.9, 37.9, 25.8, -57.74, -57.74 };
float topz[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

float laengeOberarm = 40.0;
float laengeUnterarm = 138.0;

int beta[6] = { 267, 213, 150, 93, 30, 333};
int pwmpin[6] = {10,8,7,12,11,9};
int analogpin[6] = {2,4,5,0,1,3};
int flat[6] = {4,166,4,161,7,147};
int upright[6] = {90,71,94,66,99,51};
//The setup function is called once at startup of the sketch



Hexapod nils(laengeOberarm,laengeUnterarm,basex,basey,basez,topx,topy,topz,beta,pwmpin,analogpin,flat,upright);


void setup() {
// Add your initialization code here
	Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop() {
	nils.verfahren(0.0,0.0,10.0,0.0,0.0,0.0);
	delay(5000);

//Add your repeated code here
}
