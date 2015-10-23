// Do not remove the include below
#include "Stewart_Plattform_IPF.h"
#include "Hexapod.h"
#include "Arduino.h"
#include "Joystick.h"
#include "Vector.h"
#include "LiquidCrystal.h"

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
float xwert = 0;
float ywert = 0;
bool erlaubt = true;
Vector ziel;
//------------------
//---------Lagesensor----
	float ix;
	float iy;
	float iz;
	float lastIX;
	float lastIY;
	float lastIZ;
	float readx;
	float ready;
	float readz;
	float pitchAng;
	float rollAng;
//-------------------------

/*
 * Initialisierung der Teile
 */
Hexapod nils(laengeOberarm, laengeUnterarm, defaultHeight, baseR, topR, baseWi,
		topWi, beta, pwmpin, analogpin, flat, upright);
Joystick bediener(250, 772, 255, 766, 9, 8);

LiquidCrystal LCD(31,30,32,34,36,38);

void setup() {
// Add your initialization code here
	Serial.begin(9600);
	bediener.kalibrieren();
	LCD.begin(16,2);
}

// The loop function is called in an endless loop
void loop() {
//----- Joystick bedienung ------------------------------
/*
	ziel = bediener.bewegung(1);
	xwert = xwert + (ziel.x);
	Serial.println(xwert);
	ywert = ywert + (ziel.y);
	if (xwert >20) xwert = 20;
	if (xwert <-20) xwert = -20;
	if (ywert >20) ywert = 20;
	if (ywert <-20) ywert = -20;
	if (bediener.klick()) {xwert = 0; ywert = 0;}
	nils.verfahren(0.0, 0.0, 0.0, 0.0, xwert, ywert);
	LCD.clear();
    LCD.setCursor(0,0);
    LCD.print(xwert);
    LCD.setCursor(0,1);
    LCD.print(ywert);
*/
//------------------------------------------------------

		readx = (analogRead(15) - 385.0) / 85.0;
	    ready = (analogRead(14) - 385.0) / 85.0;
	    readz = (analogRead(13) - 385.0) / 85.0;

	    lastIX = readx;
		lastIY = ready;
		lastIZ = readz;

		ix = 0.005 * readx + 0.995 * lastIX;
		iy = 0.005 * ready + 0.995 * lastIY;
		iz = 0.005 * readz + 0.995 * lastIZ;

		LCD.clear();
	    LCD.setCursor(0,0);
	    LCD.print(readx);
	    LCD.setCursor(0,1);
	    LCD.print(readz);

	    pitchAng = RAD_TO_DEG * atan(ix / sqrt(pow(iy, 2) + pow(iz, 2)));
	    rollAng = RAD_TO_DEG * atan(iy / sqrt(pow(ix, 2) + pow(iz, 2)));
	    if (abs(pitchAng) < 2.5) pitchAng = 0.0;
	    if (abs(rollAng) < 2.5) rollAng = 0.0;
	    nils.verfahren(0.0, 0.0, 0.0, 0.0, pitchAng, -rollAng);
	    delay(100);

}

