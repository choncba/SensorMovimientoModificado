// Firmware para Attiny13/85 en reemplazo del stock de los sensores de movimiento inhalámbricos
// Hardware modificado para funcionar cableado
// Branch de prueba dejando original la entrada del sensor y utilizando el pin digital por interrupcion
#include <Arduino.h>

// Pines			// Modificaciones en el hardware
#define TEST_PIN  5 // Al pulsador de test, Sin usar
#define RFOUT_PIN 3 // Salida RF Desconectado, solo uso el led
#define LED 	  RFOUT_PIN
#define BUZZ_PIN  4 // Buzzer removido, Lo uso ahora para la salida a colector abierto
#define OUT		  BUZZ_PIN
#define VBAT_PIN  0 // Divisor para leer valor de batería, Sin usar
#define SENSE_PIN 1 // Entrada movimiento, este pin es digital, se trabaja por interrupcion
#define REC_PIN   2 // conectado al jumper para grabar el sensor rf a la central
#define MOV_PIN   SENSE_PIN 

// Divisor resistivo en la salida
// Vout = Vcc/(R1+R2)*R2 = 5v
// c/Vcc=12v, R1=1k, R2 = 

void setup()
{
	pinMode(LED,OUTPUT);
  	pinMode(OUT,OUTPUT);
	pinMode(MOV_PIN,INPUT_PULLUP);
}

void loop()
{
	if(digitalRead(MOV_PIN) == LOW){
		digitalWrite(LED,HIGH);
		digitalWrite(OUT,HIGH);
		delay(1000);
		while(digitalRead(MOV_PIN) == LOW){
			delay(100);
		}
		digitalWrite(LED,LOW);
		digitalWrite(OUT,LOW);
	}
}