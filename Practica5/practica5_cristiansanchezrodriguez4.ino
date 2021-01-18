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

// -- MODULO DE LUCES -- //
enum constants
{
  	MAX_BUFFER_SIZE = 64,
  	LENGTH = 9,
  	PIN_RGB_RED = 11,
  	PIN_RGB_BLUE = 10,
  	PIN_RGB_GREEN = 9
};

enum rgb
{
  	RED = 1,
  	GREEN,
  	BLUE,
  	OFF
};

// Variables globales
char buffer [MAX_BUFFER_SIZE];
int value, pin_value, pin_state, sw;

const int INPUT_PINS[] = {},
  		  OUTPUT_PINS[] = {PIN_RGB_RED,
                           PIN_RGB_BLUE,
                           PIN_RGB_GREEN};

// -- Métodos generales -- //
// Para inicializar los pins
void init_pins()
{
  for (int i = 0; i < sizeof(INPUT_PINS); i++)
    pinMode(INPUT_PINS[i], INPUT);
  for (int i = 0; i < sizeof(OUTPUT_PINS); i++)
    pinMode(OUTPUT_PINS[i], OUTPUT);
}

// Apaga las salidas
void turn_off_outputs()
{
  //Serial.println("Turning off pins...");
  for (int i = 0; i < sizeof(OUTPUT_PINS); i++)
    digitalWrite(OUTPUT_PINS[i], LOW);
}

// -- SETUP -- //
void setup()
{
  // Se inicializa la velocidad de transmisión
  Serial.begin (9600);  
  init_pins();  

  value = 0;
  pin_value = 99;
  pin_state = LOW;
  sw = 0;
}

// -- LOOP -- //
void loop()
{
  if (Serial.available()) {  
    value = Serial.parseInt();

    Serial.println("Value: "+String(value));
    Serial.println("SW --> "+String(sw));

    if (value != 0) {          	
      switch (sw) {
        case 0:
        pin_value = value;
        sw = 1;
        break;

        case 1:
        pin_state = value;
        sw = 2;
        break;

        default:
        Serial.println("Unexpected!");
        turn_off_outputs();
        sw = 0;
      }            
    } else {
      sw = 0;
      //Serial.println("Doing stuff...");
      turn_off_outputs();
      if ((pin_value != 99) &&
          (pin_state != 9)) 
        digitalWrite(pin_value, pin_state);
    }      	      	
  }
  delay (100);
}