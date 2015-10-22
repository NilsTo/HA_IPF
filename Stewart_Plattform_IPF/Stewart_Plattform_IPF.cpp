// Do not remove the include below
#include "Stewart_Plattform_IPF.h"
#include "Hexapod.h"
#include "Arduino.h"
#include "Joystick.h"
#include "Vector.h"

/*
 * Geometrische Daten der Basis und Top. Winkel sind die die mathematisch positiv eingezeichneten Winkel
 * zwischen lokalem KKS und den Ankerpunkten.
 */
float baseWi[6] = { 176.9176, 123.0772, 56.9228, 3.0772, 296.9228, 243.0772 };
float topWi[6] = { 156.2695, 143.7305, 36.2695, 23.7305, 276.2694, 263.7305 };
float baseR = 86.6870;
float topR = 64.1185;
/*
 * Geometrische Details deines Arms.
 */
float laengeOberarm = 40.0;
float laengeUnterarm = 138.0;
//Iterativ berechnete Mittelposition - dann gilt z-Achse +-28mmm rollAngle +-25° pitchAngle +-27° yawAngle +-50 -- Kombinationen geringer
float defaultHeight = 145.0;
/*
 * Details der Servos. Beta beschreibt den eingezeichneten Winkel zwischen Oberarmfläche und X-Achse
 * des lokalen KKS des Baseplates.(siehe mathematische Herleitung)
 * Die Pins spiegeln die Belegung auf dem Arduino-Board wider.
 * Flat u. Upright sind die Winkel der Servos bei waagerechter u. senkrechter Stellung.
 */
float beta[6] = { 240, 60, 120, -60, 0, 180 };
int pwmpin[6] = { 10, 8, 7, 12, 11, 9 };
int analogpin[6] = { 2, 4, 5, 0, 1, 3 };
int flat[6] = { 4, 166, 4, 161, 7, 147 };
int upright[6] = { 90, 71, 94, 66, 99, 51 };

//-----------------------
	float xwert;
	float ywert;
	Vector ziel;
//------------------
/*
 * Initialisierung des Hexapods
 */
Hexapod nils(laengeOberarm, laengeUnterarm, defaultHeight, baseR, topR, baseWi,
		topWi, beta, pwmpin, analogpin, flat, upright);
Joystick bediener(486,259,800,474,265,794,2,3);

void setup() {
// Add your initialization code here
	Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop() {
	ziel = bediener.bewegung(1);
	xwert = ziel.x;
	ywert = ziel.y;
	Serial.println(xwert);
	Serial.println(ywert);
	delay(1000);

//Add your repeated code here
}
