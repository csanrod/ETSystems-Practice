#include <inttypes.h>

// #define USE_THREAD_NAMES	1

class Thread{
protected:
	unsigned long interval;
	unsigned long last_run;
	unsigned long _cached_next_run;
	void runned(unsigned long time);
	void runned() { runned(millis()); }
	void (*_onRun)(void);		

public:
	bool enabled;
	int ThreadID;

	#ifdef USE_THREAD_NAMES
		// Thread Name (used for better UI).
		String ThreadName;			
	#endif

	Thread(void (*callback)(void) = NULL, unsigned long _interval = 0);
	virtual void setInterval(unsigned long _interval);
	virtual bool shouldRun(unsigned long time);
	bool shouldRun() { return shouldRun(millis()); }
	void onRun(void (*callback)(void));
	virtual void run();
};

/* ------------------------------------------------ */

Thread::Thread(void (*callback)(void), unsigned long _interval){
	enabled = true;
	onRun(callback);
	_cached_next_run = 0;
	last_run = millis();

	ThreadID = (int)this;
	#ifdef USE_THREAD_NAMES
		ThreadName = "Thread ";
		ThreadName = ThreadName + ThreadID;
	#endif

	setInterval(_interval);
};

void Thread::runned(unsigned long time){
	// Saves last_run
	last_run = time;

	// Cache next run
	_cached_next_run = last_run + interval;
}

void Thread::setInterval(unsigned long _interval){
	// Save interval
	interval = _interval;

	// Cache the next run based on the last_run
	_cached_next_run = last_run + interval;
}

bool Thread::shouldRun(unsigned long time){
	// If the "sign" bit is set the signed difference would be negative
	bool time_remaining = (time - _cached_next_run) & 0x80000000;

	// Exceeded the time limit, AND is enabled? Then should run...
	return !time_remaining && enabled;
}

void Thread::onRun(void (*callback)(void)){
	_onRun = callback;
}

void Thread::run(){
	if(_onRun != NULL)
		_onRun();

	// Update last_run and _cached_next_run
	runned();
}
/* ------------------------------------------------ */

#include "inttypes.h"

#define MAX_THREADS		15

class ThreadController: public Thread{
protected:
	Thread* thread[MAX_THREADS];
	int cached_size;
public:
	ThreadController(unsigned long _interval = 0);
	void run();
	bool add(Thread* _thread);
	void remove(int _id);
	void remove(Thread* _thread);
	void clear();
	int size(bool cached = true);
	Thread* get(int index);
};
/* ------------------------------------------------ */
ThreadController::ThreadController(unsigned long _interval): Thread(){
	cached_size = 0;

	clear();
	setInterval(_interval);

	#ifdef USE_THREAD_NAMES
		// Overrides name
		ThreadName = "ThreadController ";
		ThreadName = ThreadName + ThreadID;
	#endif
}

/*
	ThreadController run() (cool stuf)
*/
void ThreadController::run(){
	// Run this thread before
	if(_onRun != NULL)
		_onRun();

	unsigned long time = millis();
	int checks = 0;
	for(int i = 0; i < MAX_THREADS && checks < cached_size; i++){
		// Object exists? Is enabled? Timeout exceeded?
		if(thread[i]){
			checks++;
			if(thread[i]->shouldRun(time)){
				thread[i]->run();
			}
		}
	}

	// ThreadController extends Thread, so we should flag as runned thread
	runned();
}


/*
	List controller (boring part)
*/
bool ThreadController::add(Thread* _thread){
	// Check if the Thread already exists on the array
	for(int i = 0; i < MAX_THREADS; i++){
		if(thread[i] != NULL && thread[i]->ThreadID == _thread->ThreadID)
			return true;
	}

	// Find an empty slot
	for(int i = 0; i < MAX_THREADS; i++){
		if(!thread[i]){
			// Found a empty slot, now add Thread
			thread[i] = _thread;
			cached_size++;
			return true;
		}
	}

	// Array is full
	return false;
}

void ThreadController::remove(int id){
	// Find Threads with the id, and removes
	for(int i = 0; i < MAX_THREADS; i++){
		if(thread[i]->ThreadID == id){
			thread[i] = NULL;
			cached_size--;
			return;
		}
	}
}

void ThreadController::remove(Thread* _thread){
	remove(_thread->ThreadID);
}

void ThreadController::clear(){
	for(int i = 0; i < MAX_THREADS; i++){
		thread[i] = NULL;
	}
	cached_size = 0;
}

int ThreadController::size(bool cached){
	if(cached)
		return cached_size;

	int size = 0;
	for(int i = 0; i < MAX_THREADS; i++){
		if(thread[i])
			size++;
	}
	cached_size = size;

	return cached_size;
}

Thread* ThreadController::get(int index){
	int pos = -1;
	for(int i = 0; i < MAX_THREADS; i++){
		if(thread[i] != NULL){
			pos++;

			if(pos == index)
				return thread[i];
		}
	}

	return NULL;
}
/* ------------------------------------------------ */
template <int N>
class StaticThreadController: public Thread{
protected:
        //since this is a static controller, the pointers themselves can be const
	//it should be distinguished from 'const Thread* thread[N]'
	Thread * const thread[N];
public:
	template <typename... T>
        StaticThreadController(T... params) :
		Thread(),
		thread{params...}
	{ 
	#ifdef USE_THREAD_NAMES
		// Overrides name
		ThreadName = "StaticThreadController ";
		ThreadName = ThreadName + ThreadID;
	#endif
	};

	// run() Method is overrided
	void run() override
	{
		// Run this thread before
		if(_onRun != nullptr && shouldRun())
			_onRun();

		for(int i = 0; i < N; i++){
			// Is enabled? Timeout exceeded?
			if(thread[i]->shouldRun()){
				thread[i]->run();
			}
		}

		// StaticThreadController extends Thread, so we should flag as runned thread
		runned();
	}

	// Return the quantity of Threads
	static constexpr int size() { return N; };

	// Return the I Thread on the array
	// Returns nullptr if index is out of bounds
	Thread* get(int index) {
		return (index >= 0 && index < N) ? thread[index] : nullptr;
	};

	// Return the I Thread on the array
	// Doesn't perform any bounds checks and behaviour is
	// unpredictable in case of index > N
	Thread& operator[](int index) {
		return *thread[index];
	};
};
/* ---------------------- MAIN ---------------------- */
/* -- INCLUDES -- */
// Lo anterior sería lo necesario para Arduino Threads
#include <LiquidCrystal.h>
#include <avr/wdt.h>

/* -- DEFINES -- */
// R --> Pin red del RGB
// G --> Pin green del RGB
// RESTART --> Para simular el funcionamiento del watchdog
// NOTE --> Establece la nota a la que sonara el piezoeléctrico
#define R 10 
#define G 9
#define RESTART asm("jmp 0x0000")
#define NOTE 440

// Variables para usar ArduinoThreads
ThreadController controller = ThreadController();
Thread led1 = Thread(), lcd_thrd = Thread(), pir_thrd = Thread(), 
		rgb_thrd = Thread(), tmp_thrd = Thread(), HC_thrd = Thread();

// Definición de variables genéricas y pines
const int ledPin = 11, soundPin = 13, PIRpin = 12;
int buttonState = 0, value = 0, lectura = 0,
	pirState = LOW, ledState = LOW,
	rgb_It = 3, red_RGB = 0, green_RGB = 0,
	lcd_switch = 0, LCD_counter = 0, par = 0, 
	clear_switch = 0, buttonState2 = 0;

double distancia = 0, factor_de_conversion = 0.01715, tmp = 0.0;
int outPins[] = {ledPin, A3, R, G, A1, A2};

LiquidCrystal lcd(8, 7, 6, 5, 4, 3);
unsigned long current_time;

/* -- CALLBACKS -- */
void led1_CB(){
  // Cambia el estado de un led cada segundo
  if(ledState == LOW){
  	digitalWrite(A1, HIGH);
    ledState = HIGH;
  }else{
    digitalWrite(A1, LOW);
    ledState = LOW;
  }
}

void LCD_CB(){
  // Controla el display del LCD
  //
  // Se actualiza cada 0'5s y va cambiando entre temperatura,
  // distancia y movimiento cada 10s, mostrando además, el tiempo
  // transcurrido en la línea inferior.
  lcd.clear();
  par++;
  if((par%2) == 0)
    // Suma uno cada dos ejecuciones (cada 1s)
  	LCD_counter++;
  
  switch(lcd_switch){
  // Máquina de estados
  // 	0 --> Temperatura
  //	1 --> Distancia
  // 	2 --> Movimiento
    case(0):
    	lcd.print("Temperatura:");
    	lcd.print(tmp);
        
        if(((LCD_counter%10) == 0)&&((par%2) == 0))
          	lcd_switch = 1;
    	break;
    case(1):
        if (distancia >= 334.7){
          lcd.print("Sin deteccion");
        }else{
          lcd.print("Obstaculo:");
          lcd.print(distancia);
        }
    	if(((LCD_counter%10) == 0)&&((par%2) == 0))
    		lcd_switch = 2;
    	break;
    case(2):
        if (pirState == HIGH){
          lcd.print("Movimiento: SI  ");
          lcd.print(tmp);
        }else{
          lcd.print("Movimiento: NO  ");
          lcd.print(tmp);
        }
    	if(((LCD_counter%10) == 0)&&((par%2) == 0))
    		lcd_switch = 0;
    	break;    
  }
  // Display del tiempo transcurrido.
  lcd.setCursor(0, 1);
  lcd.print(LCD_counter);
  lcd.print(" s");
  lcd.setCursor(0, 0);
}

void PIR_CB(){
  // Callback del sensor de movimiento, cada 2s comprueba.
  pirState = digitalRead(PIRpin);
  if (pirState == HIGH){
    red_RGB = 255;
    green_RGB = 0;
    rgb_It = 0;
  }else{    
  }
}

void RGB_CB(){
  // Callback del RGB, actualiza los estados del RGB cada 0'5s
  if(pirState == LOW){
    rgb_It++;
    switch(rgb_It) {
      case(1):
      	red_RGB = 255;
      	green_RGB = 155;
      	break;
      case(2):
      	red_RGB = 0;
      	green_RGB = 155;
      	break;
      default:
      	red_RGB = 0;
      	green_RGB = 0;
      	break;      	
    }
  }
  analogWrite(R, red_RGB);
  analogWrite(G, green_RGB);
}

void TMP_CB(){
  // Se encarga de tomar la medida de la temperatura cada 1s, 
  // además, suena a través del piezoeléctrico si pasa de 60º.
  lectura = analogRead(0);
  tmp = (lectura * (500.0/1023.0)) - 50.0;
  if (tmp > 60){
    tone(soundPin, NOTE);
  } else {
    noTone(soundPin);
  }
}
void HC_CB(){
  // Callback del sensor de ultrasonidos, toma la distancia cada
  // medio segundo.
  digitalWrite(A3,HIGH);
  delayMicroseconds(10);
  digitalWrite(A3,LOW);

  distancia = factor_de_conversion*pulseIn(A4,HIGH);
}

/* -- SETUP -- */
void setup()
{
  Serial.begin(9600); // Para trazabilidad
  lcd.display();
  
  // INPUTS   
  pinMode(2, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(PIRpin, INPUT);
  
  // OUTPUTS 
  int i = 0;
  for (i = 0; i<4; i++)	{
  	pinMode(outPins[i], OUTPUT);
  }
  lcd.begin(16, 2);
  
  // THREADS   
  led1.enabled = true;
  led1.setInterval(1000);
  led1.onRun(led1_CB);
  
  lcd_thrd.enabled = true;
  lcd_thrd.setInterval(500);
  lcd_thrd.onRun(LCD_CB);
  
  pir_thrd.enabled = true;
  pir_thrd.setInterval(2000);
  pir_thrd.onRun(PIR_CB);
  
  rgb_thrd.enabled = true;
  rgb_thrd.setInterval(500);
  rgb_thrd.onRun(RGB_CB);
  
  tmp_thrd.enabled = true;
  tmp_thrd.setInterval(1000);
  tmp_thrd.onRun(TMP_CB);
  
  HC_thrd.enabled = true;
  HC_thrd.setInterval(500);
  HC_thrd.onRun(HC_CB);
  
  controller.add(&led1);
  controller.add(&lcd_thrd);
  controller.add(&pir_thrd);
  controller.add(&rgb_thrd);
  controller.add(&tmp_thrd);
  controller.add(&HC_thrd);
	
  // WATCHDOG 
  //
  // Código comentado porque no funciona en este simulador,
  // Simulación hecha de manera manual.
  
  //wdt_disable();
  //wdt_enable(WDTO_4S);
}

/* -- LOOP -- */
void loop()
{
  controller.run(); // Para poner en funcionamiento los threads
  
  // LED controlado con el botón de la izquierda 
  buttonState = digitalRead(2);
  if (buttonState == HIGH) {
    digitalWrite(A2, HIGH);
  } else {
    digitalWrite(A2, LOW);
  }
  
  // LED que se enciende/apaga progresivamente 
  for (int percent = 0; percent <= 100; percent++){
    value = (255/100)*percent;
    analogWrite(ledPin, value); 
  }
  for (int percent = 100; percent >= 0; percent--){
    value = (255/100)*percent;
    analogWrite(ledPin, value); 
  }
  
  // Simulación del WATCHDOG 
  buttonState2 = digitalRead(A5);
  if (buttonState2 == HIGH) {
    current_time = millis();
    while(1){
      if((millis()-current_time) > 4000)
        RESTART;
      delay(1000);
    }
  }
  //wdt_reset();
  delay(30); // Para mejorar el funcionamiento del simulador 
}