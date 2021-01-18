/* ------------------------------------------------------------ */
// Programador: Cristian Sánchez Rodríguez

// Asignatura: Sistemas empotrados y de tiempo real

// Descripción: Este sistema simula un sistema de funcional 
//				para un vehículo
//
//				Se compone de un módulo de temperatura con alarma, 
//				un módulo de aparcamiento que te advierte de la 
//				cercanía de un obstáculo cuando se activa, y un
//				módulo de luces activado a través de un botón.
/* ------------------------------------------------------------ */

// -- MODULO DE DISTANCIA -- //
#include <Wire.h>

#define I2C_DIST_ADDRESS 12
#define PAYLOAD_SIZE 2

#define NOTE 220

enum pin 
{
  PIN_GREEN = 7,
  PIN_RED,
  PIN_SOUND = 12,
  PIN_HC_TRIG = A2,
  PIN_HC_ECHO = A3
};

// Variables globales
int alert;
double dist, factor;
const int INPUT_PINS[] = {PIN_HC_ECHO},
  		  OUTPUT_PINS[] = {PIN_GREEN,
                           PIN_RED,
                           PIN_HC_TRIG};

// -- Métodos generales -- //
// Para inicializar los pins
void init_pins()
{
  for (int i = 0; i < sizeof(INPUT_PINS); i++)
    pinMode(INPUT_PINS[i], INPUT);
  for (int i = 0; i < sizeof(OUTPUT_PINS); i++)
    pinMode(OUTPUT_PINS[i], OUTPUT);
}

// Lee la distancia al obstáculo
void read_dist ()
{
  digitalWrite(PIN_HC_TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_HC_TRIG,LOW);

  dist = factor*pulseIn(PIN_HC_ECHO, HIGH);
}

// Activa o no la alerta según estime el módulo central
void alarm_2 ()
{
  if (alert) {
    tone(PIN_SOUND, NOTE);
    digitalWrite(PIN_GREEN, LOW);
  	digitalWrite(PIN_RED, HIGH);    
  } else {
    noTone(PIN_SOUND);
    digitalWrite(PIN_GREEN, HIGH);
  	digitalWrite(PIN_RED, LOW);
  }
}

// -- SETUP -- //
void setup()
{
  // Inicia I2C con la dirección al no ser master
  Wire.begin(I2C_DIST_ADDRESS);
  
  Serial.begin(9600);
  init_pins();
  
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_RED, LOW);
  
  factor = 0.01715;
  dist = 0.0;
  alert = 0;
}

// -- LOOP -- //
void loop()
{
  read_dist();
  Wire.onRequest(requestEvents);
  Wire.onReceive(receiveEvents);
  alarm_2();
  
  delay(100);
}

// -- METODOS I2C -- //
// Solicitudes
void requestEvents()
{
  //Serial.println(">> Request received, sending "+String((int) dist));
  Wire.write((int) dist); 
}

// Recepciones
void receiveEvents (int numBytes)
{
  //Serial.println(">> Reception waiting...");
  alert = Wire.read();
  //Serial.println("\tValue: "+String(alert));
  //Serial.println("\tBytes: "+String(numBytes));
}