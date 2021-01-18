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

// -- MASTER -- //
#include <Wire.h>
#include <LiquidCrystal.h>

#define I2C_TMP_ADDRESS 11
#define I2C_DIST_ADDRESS 12
#define PAYLOAD_SIZE 2

enum pin
{
  PIN_BUTTON = 2,
  PIN_BUTTON_2 = 4,
  PIN_LCD_DB7 = 7,
  PIN_LCD_DB6,
  PIN_LCD_DB5,
  PIN_LCD_DB4,
  PIN_LCD_E,
  PIN_LCD_RS
};

enum send_msg
{
	RED = 0,
  	GREEN,
  	BLUE,
  	OFF
};

// Mensajes UART
char red_on [] = "P=11&S=1\n",
	 blue_on [] = "P=10&S=1\n",
	 green_on [] = "P=09&S=1\n",
	 all_off [] = "P=99&S=9\n"; // msg default para apagar

// Variables globales
int tmp_value, sound_on,
	dist, alert, msg_switcher,
	button_state_2;
volatile int button_state;

const int INPUT_PINS[] = {PIN_BUTTON,
                          PIN_BUTTON_2},
  		  OUTPUT_PINS[] = {};

// LCD
LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_E, 
                  PIN_LCD_DB4, PIN_LCD_DB5, 
                  PIN_LCD_DB6, PIN_LCD_DB7);

// -- ISR Pulsador -- //
void button_isr()
{
	noInterrupts();  
 	button_state = !button_state;
  	interrupts();
}

// -- Métodos generales -- //
// Para inicializar los pins
void init_pins()
{
	for (int i = 0; i < sizeof(INPUT_PINS); i++)
    	pinMode(INPUT_PINS[i], INPUT);
    for (int i = 0; i < sizeof(OUTPUT_PINS); i++)
    	pinMode(OUTPUT_PINS[i], OUTPUT);
}
// I2C Temperatura
// NOTA: El simulador no registra bien cambios bruscos de tmp
void tmp_communication()
{
  // Maneja la solicitud del slave1, solicita n de slave1
  Wire.requestFrom(I2C_TMP_ADDRESS, 1);
  tmp_value = Wire.read();
  //Serial.println("(MASTER) From TMP: "+String(tmp_value));
  
  lcd.clear();
  lcd.print("Temperatura: ");
  lcd.print(tmp_value);
  lcd.setCursor(0, 1);
  lcd.print("");
  lcd.setCursor(0, 0);
  
  if (tmp_value > 60)
    sound_on = 1;
  else
    sound_on = 0;
  
  Wire.beginTransmission(I2C_TMP_ADDRESS);
  Wire.write(sound_on);
  //Serial.println("(MASTER) To TMP: "+String(sound_on));
  Wire.endTransmission();
}

// I2C distancia de aparcamiento
void parking()
{
  // Maneja la solicitud del slave1, solicita n de slave1
  Wire.requestFrom(I2C_DIST_ADDRESS, 1);
  dist = Wire.read();
  //Serial.println("(MASTER) From DIST: "+String(dist));
  
  lcd.clear();
  lcd.print("Distancia: ");
  lcd.print(dist);
  
  
  if (dist < 30) {
    alert = 1;
    lcd.setCursor(0, 1);
    lcd.print("Obstaculo!");
  	lcd.setCursor(0, 0);
  } else {
    alert = 0;
    lcd.setCursor(0, 1);
    lcd.print("");
  	lcd.setCursor(0, 0);
  }
 
  Wire.beginTransmission(I2C_DIST_ADDRESS);
  Wire.write(alert);
  //Serial.println("(MASTER) To TMP: "+String(alert));
  Wire.endTransmission();
}

// UART controlado por el pulsador 2
void lights_uart()
{
  button_state_2 = digitalRead(PIN_BUTTON_2);
  if (button_state_2) {     
    //Serial.println("Button pressed");

    switch (msg_switcher) {
      case RED:
      send_msg(red_on);
      msg_switcher = GREEN;
      break;

      case GREEN:
      send_msg(green_on);
      msg_switcher = BLUE;
      break;

      case BLUE:
      send_msg(blue_on);
      msg_switcher = OFF;
      break;

      case OFF:
      send_msg(all_off);
      msg_switcher = RED;
      break;

      default:
      Serial.println("Error, something unexpected happened...\n");
      msg_switcher = OFF;
    }        
  }
}

// Submetodo necesario para UART, transmite el msg
void send_msg(char msg[])
{
  if (Serial.availableForWrite()) {           	
    Serial.write(msg);

    // Se espera a que se transmita todo el msg y
    // retoma la ejecución normal.
    Serial.flush();
  }
}

// -- SETUP -- //
void setup()
{
  // En maestro puede no llevar args. Init de la dir.
  Wire.begin();
  // V de transmision en baudios
  Serial.begin(9600);
  lcd.begin(16, 2); 
  //Serial.println("INIT MASTER");
  
  init_pins();
  
  sound_on = 0;
  alert = 0;
  button_state = LOW;
  button_state_2 = LOW;
  msg_switcher = RED;
  
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), 
                  button_isr, 
                  RISING);
}

// -- LOOP -- //
void loop()
{
  //Serial.println(button_state);
  int it = 0;
  if (button_state)      
  	parking();
  else {      
    tmp_communication();
    lights_uart();     
  }  
  delay(100);
}