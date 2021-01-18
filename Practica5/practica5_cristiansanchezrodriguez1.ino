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

// -- MODULO DE TEMPERATURA -- //
#include <Wire.h>

#define I2C_TMP_ADDRESS 11
#define PAYLOAD_SIZE 2

enum pins {
  PIN_TMP = A3,
  PIN_SOUND = 12
};

enum constants {
  NOTE = 440
};

// Variables globales
int tmp_value, sound_on;

const int INPUT_PINS[] = {PIN_TMP},
  		  OUTPUT_PINS[] = {};

// -- Métodos generales -- //
// Para inicializar los pins
void init_pins()
{
  for (int i = 0; i < sizeof(INPUT_PINS); i++)
    pinMode(INPUT_PINS[i], INPUT);
  for (int i = 0; i < sizeof(OUTPUT_PINS); i++)
    pinMode(OUTPUT_PINS[i], OUTPUT);
}

// Toma medidas de temperatura
void read_tmp()
{
  tmp_value = analogRead(PIN_TMP);
  tmp_value = (tmp_value * (500.0/1023.0)) - 50.0;
}

// Activa o desactiva la alerta en función del módulo central
void alarm ()
{
  if (sound_on)
    tone(PIN_SOUND, NOTE);
  else 
    noTone(PIN_SOUND);
}

// -- SETUP -- //
void setup()
{
  // Inicia I2C con la dirección al no ser master
  Wire.begin(I2C_TMP_ADDRESS);
  Serial.begin(9600);
  //Serial.println("INIT TMP");
  
  read_tmp();
  sound_on = 0;
}

// -- LOOP -- //
void loop()
{
  read_tmp();
  
  Wire.onRequest(requestEvents);
  Wire.onReceive(receiveEvents);
  
  alarm();
  delay(100);
}

// -- METODOS I2C -- //
// Solicitudes
void requestEvents()
{
  //Serial.println(">> Request received, sending "+String(tmp_value));
  Wire.write(tmp_value); 
}

// Recepciones
void receiveEvents (int numBytes)
{
  //Serial.println(">> Reception waiting...");
  sound_on = Wire.read();
  //Serial.println("\tValue: "+String(sound_on));
  //Serial.println("\tBytes: "+String(numBytes));
}