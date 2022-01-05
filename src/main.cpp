// Firmware para Attiny13/85 en reemplazo del stock de los sensores de movimiento inhalámbricos
// Hardware modificado para funcionar cableado
#include <Arduino.h>

// Pines			// Modificaciones en el hardware
#define TEST_PIN  5 // Al pulsador de test, Sin usar
#define RFOUT_PIN 3 // Salida RF Desconectado, solo uso el led
#define LED 	  RFOUT_PIN
#define BUZZ_PIN  4 // Buzzer removido, Lo uso ahora para la salida a colector abierto
#define OUT		  BUZZ_PIN
#define VBAT_PIN  0 // Divisor para leer valor de batería, Sin usar
#define SENSE_PIN 1 // Entrada movimiento, puenteado al pin PB2 que es una entrada A/D
#define REC_PIN   2 // originalmente conectado al jumper para grabar el sensor rf a la central
#define MOV_PIN   REC_PIN // También A1

void setup()
{
	pinMode(LED,OUTPUT);
  	pinMode(OUT,OUTPUT);
	pinMode(MOV_PIN,INPUT);
}

void loop()
{
	int val1 = 0;
	int val2 = 0;
	uint8_t i = 0;
	// La salida del Operacional del sensor sin movimiento está estable aproximadamente a 2V,
	// Cuando se produce movimiento va a 0 y hasta Vcc (3,6V), después vuelve al valor estable
	for(i=0;i<10;i++)					// Promedio 10 lecturas para el primer valor
	{
		val1 += analogRead(MOV_PIN);
		delay(20);
	}
	int prom1 = val1/10;
	delay(500);							// Espero 500 mSeg para que el sensor se estabilice
	for(i=0;i<10;i++)					// Promedio otras 10 lecturas para el segundo valor
	{
		val2 += analogRead(MOV_PIN);
		delay(20);
	}
	int prom2 = val2/10;

	if(abs(prom1-prom2)>100)			// En las pruebas, si la diferencia supera 100, detecto movimiento
	{							
		digitalWrite(LED,HIGH);
    	digitalWrite(OUT,HIGH);
		delay(2000);
	}
	else
	{
		digitalWrite(LED,LOW);
    	digitalWrite(OUT,LOW);
	}
	
}