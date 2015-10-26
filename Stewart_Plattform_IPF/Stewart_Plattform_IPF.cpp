//------ Inclusions -----------------------
#include "Stewart_Plattform_IPF.h"
#include "Hexapod.h"
#include "Arduino.h"
#include "Joystick.h"
#include "Vector.h"
#include "LiquidCrystal.h"
#include "Robot.h"
//-----------------------------------------

//------------- Pin u. Wert Definitionen ------------------------
//---- LCD ---------
#define RS 31
#define ENABLE 30
#define D4 32
#define D5 34
#define D6 36
#define D7 38
//---- Servo -------
int pwmpin[6] = { 10, 8, 7, 12, 11, 9 };
int analogpin[6] = { 2, 4, 5, 0, 1, 3 };
//---- Joystick ----
#define XAXPIN 9
#define YAXPIN 8
#define XMIN 250
#define XMAX 772
#define YMIN 255
#define YMAX 766
//---- Taster ------
#define T1PIN 22
#define T2Pin 23
#define T3PIN 24
#define T4PIN 25
#define T5Pin 26
//---- Lagesensor --
#define XACCPIN 15
#define YACCPIN 14
#define ZACCPIN 13
#define BIAS 385.0
#define FAKTOR 85.0
//----------------------------------------------------------------

//------------- Hexapod ------------------------------------------
/*
 * Geometrische Daten der Basis und Top. Winkel sind die die mathematisch positiv eingezeichneten Winkel
 * zwischen lokalem KKS und den Ankerpunkten.
 */
float baseWi[6] = { 176.9176, 123.0772, 56.9228, 3.0772, 296.9228, 243.0772 };
float topWi[6] = { 156.2695, 143.7305, 36.2695, 23.7305, 276.2694, 263.7305 };
float baseR = 86.6870;
float topR = 64.1185;
//Geometrische Details eines Arms.
float laengeOberarm = 40.0;
float laengeUnterarm = 138.0;
//Iterativ berechnete Mittelposition - dann gilt z-Achse +-28mmm rollAngle +-25� pitchAngle +-27� yawAngle +-50 -- Kombinationen geringer
float defaultHeight = 145.0;
/*
 * Details der Servos. Beta beschreibt den eingezeichneten Winkel zwischen Oberarmfl�che und X-Achse
 * des lokalen KKS des Baseplates.(siehe mathematische Herleitung)
 * Flat u. Upright sind die Winkel der Servos bei waagerechter u. senkrechter Stellung.
 */
float beta[6] = { 240, 60, 120, -60, 0, 180 };
int flat[6] = { 4, 166, 4, 161, 7, 147 };
int upright[6] = { 90, 71, 94, 66, 99, 51 };
//---------------------------------------------------------------

//-------- Allgemein -------------
bool menu = true;
bool mod1 = false;
bool mod2 = false;
bool mod3 = false;
//-------- Joystick --------------
float xwert = 0;
float ywert = 0;
bool erlaubt = true;
Vector ziel;
//-------- Lagesensor ------------
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
//-------- Roboter ---------------
bool erstellt = false;
//-------------------------

//--------- Initialisierung der Teile -----------------------------
Hexapod stewart(laengeOberarm, laengeUnterarm, defaultHeight, baseR, topR,
		baseWi, topWi, beta, pwmpin, analogpin, flat, upright);
Joystick bediener(XMIN, XMAX, YMIN, YMAX, XAXPIN, YAXPIN);

LiquidCrystal LCD(RS, ENABLE, D4, D5, D6, D7);

Robot roboter(pwmpin, analogpin, flat, upright, 10);
//-----------------------------------------------------------------

//-------- SETUP --------------------------------------------------
void setup() {
	Serial.begin(9600);
	bediener.kalibrieren();
	LCD.begin(16, 2);
	pinMode(T1PIN, INPUT);
	pinMode(T2PIN, INPUT);
	pinMode(T3PIN, INPUT);
	pinMode(T4PIN, INPUT);
	pinMode(T5PIN, INPUT);
}
//-----------------------------------------------------------------

//-------- LOOP ---------------------------------------------------
void loop() {
//------ Menue -----------------------------------------
	if (menu) {
		LCD.clear();
		LCD.setCursor(0, 0);
		LCD.print("T1:Joystick");
		LCD.setCursor(0, 1);
		LCD.print("T2:Lagesensor");
		delay(500);
		LCD.clear();
		LCD.setCursor(0, 0);
		LCD.print("T3:Roboter");
		if (digitalRead(T1PIN) == LOW) {
			mod1 = true;
			menu = false;
			mod2 = false;
			mod3 = false;
		}
		if (digitalRead(T2PIN) == LOW) {
			mod2 = true;
			menu = false;
			mod1 = false;
			mod3 = false;
		}
		if (digitalRead(T3PIN) == LOW) {
			mod3 = true;
			menu = false;
			mod1 = false;
			mod2 = false;
		}
	}
//----- Joystick Modus ---------------------------------
	if (mod1 && !menu) {
		LCD.clear();
		LCD.setCursor(0, 0);
		LCD.print("JoxstickModus");
		ziel = bediener.bewegung(1);
		xwert = xwert + (ziel.x);
		Serial.println(xwert);
		ywert = ywert + (ziel.y);
		if (xwert > 20)
			xwert = 20;
		if (xwert < -20)
			xwert = -20;
		if (ywert > 20)
			ywert = 20;
		if (ywert < -20)
			ywert = -20;
		if (bediener.klick()) {
			xwert = 0;
			ywert = 0;
		}
		stewart.verfahren(0.0, 0.0, 0.0, 0.0, xwert, ywert);
		/*
		 LCD.clear();
		 LCD.setCursor(0, 0);
		 LCD.print(xwert);
		 LCD.setCursor(0, 1);
		 LCD.print(ywert);
		 */
		if (digitalRead(T5PIN) == LOW) {
			mod3 = false;
			menu = true;
			mod1 = false;
			mod2 = false;
		}
	}
//------- Lagesensor ------------------------------------
	if (mod2 && !menu) {
		readx = (analogRead(XACCPIN) - BIAS) / FAKTOR;
		ready = (analogRead(YACCPIN) - BIAS) / FAKTOR;
		readz = (analogRead(ZACCPIN) - BIAS) / FAKTOR;

		ix = 0.3 * readx + 0.7 * lastIX;
		iy = 0.3 * ready + 0.7 * lastIY;
		iz = 0.3 * readz + 0.7 * lastIZ;

		lastIX = ix;
		lastIY = iy;
		lastIZ = iz;

		LCD.clear();
		LCD.setCursor(0, 0);
		LCD.print(readx);
		LCD.setCursor(0, 1);
		LCD.print(readz);

		pitchAng = RAD_TO_DEG * atan(ix / sqrt(pow(iy, 2) + pow(iz, 2)));
		rollAng = RAD_TO_DEG * atan(iy / sqrt(pow(ix, 2) + pow(iz, 2)));
		if (abs(pitchAng) < 2.5)
			pitchAng = 0.0;
		if (abs(rollAng) < 2.5)
			rollAng = 0.0;
		stewart.verfahren(0.0, 0.0, 0.0, 0.0, pitchAng, -rollAng);
		delay(100);
		if (digitalRead(T5PIN) == LOW) {
			mod3 = false;
			menu = true;
			mod1 = false;
			mod2 = false;
		}
	}
	if (mod3 && !menu) {
		if (!erstellt) {
			roboter.kalibrieren();
			erstellt = true;
		}
		if (digitalRead(T1PIN) == LOW && mod3) {
			roboter.speichern();
		}
		if (digitalRead(T2PIN) == LOW && mod3) {
			roboter.ablauf();
			roboter.manuell();
		}
		if (digitalRead(T5PIN) == LOW) {
			mod3 = false;
			menu = true;
			mod1 = false;
			mod2 = false;
			erstellt = false;
		}
		// TODO LCD einbinden.
	}
}
//-----------------------------------------------------
