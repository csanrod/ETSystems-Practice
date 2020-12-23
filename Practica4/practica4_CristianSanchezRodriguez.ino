// -- INCLUDE TIMERONE.H -- //
#ifndef known_16bit_timers_header_
#define known_16bit_timers_header_

// Wiring-S
//
#if defined(__AVR_ATmega644P__) && defined(WIRING)
  #define TIMER1_A_PIN   5
  #define TIMER1_B_PIN   4
  #define TIMER1_ICP_PIN 6

// Teensy 2.0
//
#elif defined(__AVR_ATmega32U4__) && defined(CORE_TEENSY)
  #define TIMER1_A_PIN   14
  #define TIMER1_B_PIN   15
  #define TIMER1_C_PIN   4
  #define TIMER1_ICP_PIN 22
  #define TIMER1_CLK_PIN 11
  #define TIMER3_A_PIN   9
  #define TIMER3_ICP_PIN 10

// Teensy++ 2.0
#elif defined(__AVR_AT90USB1286__) && defined(CORE_TEENSY)
  #define TIMER1_A_PIN   25
  #define TIMER1_B_PIN   26
  #define TIMER1_C_PIN   27
  #define TIMER1_ICP_PIN 4
  #define TIMER1_CLK_PIN 6
  #define TIMER3_A_PIN   16
  #define TIMER3_B_PIN   15
  #define TIMER3_C_PIN   14
  #define TIMER3_ICP_PIN 17
  #define TIMER3_CLK_PIN 13

// Teensy 3.0
//
#elif defined(__MK20DX128__)
  #define TIMER1_A_PIN   3
  #define TIMER1_B_PIN   4
  #define TIMER1_ICP_PIN 4

// Teensy 3.1 / Teensy 3.2
//
#elif defined(__MK20DX256__)
  #define TIMER1_A_PIN   3
  #define TIMER1_B_PIN   4
  #define TIMER1_ICP_PIN 4
  #define TIMER3_A_PIN   32
  #define TIMER3_B_PIN   25
  #define TIMER3_ICP_PIN 32
  
// Teensy 3.5 / Teensy 3.6
//
#elif defined(__MK64FX512__) || defined(__MK66FX1M0__)
  #define TIMER1_A_PIN   3
  #define TIMER1_B_PIN   4
  #define TIMER1_ICP_PIN 4
  #define TIMER3_A_PIN   29
  #define TIMER3_B_PIN   30
  #define TIMER3_ICP_PIN 29
  
// Teensy-LC
//
#elif defined(__MKL26Z64__)
  #define TIMER1_A_PIN   16
  #define TIMER1_B_PIN   17
  #define TIMER1_ICP_PIN 17
  #define TIMER3_A_PIN   3
  #define TIMER3_B_PIN   4
  #define TIMER3_ICP_PIN 4

// Teensy 4.0
//
#elif defined(__IMXRT1062__)
  #define TIMER1_A_PIN   7
  #define TIMER1_B_PIN   8
  #define TIMER3_A_PIN   9
  #define TIMER3_B_PIN   6

// Arduino Mega
//
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  #define TIMER1_A_PIN   11
  #define TIMER1_B_PIN   12
  #define TIMER3_A_PIN   5
  #define TIMER3_B_PIN   2
  #define TIMER3_C_PIN   3
  #define TIMER4_A_PIN   6
  #define TIMER4_B_PIN   7
  #define TIMER4_C_PIN   8
  #define TIMER4_ICP_PIN 49
  #define TIMER5_A_PIN   46
  #define TIMER5_B_PIN   45
  #define TIMER5_C_PIN   44
  #define TIMER3_ICP_PIN 48
  #define TIMER3_CLK_PIN 47

// Arduino Leonardo, Yun, etc
//
#elif defined(__AVR_ATmega32U4__)
  #define TIMER1_A_PIN   9
  #define TIMER1_B_PIN   10
  #define TIMER1_C_PIN   11
  #define TIMER1_ICP_PIN 4
  #define TIMER1_CLK_PIN 12
  #define TIMER3_A_PIN   5
  #define TIMER3_ICP_PIN 13

//  Uno, Duemilanove, LilyPad, etc
//
#elif defined (__AVR_ATmega168__) || defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__) ||  defined (__AVR_ATmega8__)
  #define TIMER1_A_PIN   9
  #define TIMER1_B_PIN   10
  #define TIMER1_ICP_PIN 8
  #define TIMER1_CLK_PIN 5

// Minicore generic
//
#elif defined(__AVR_ATmega48PB__) || defined(__AVR_ATmega88PB__) || defined(__AVR_ATmega168PB__)
  #define TIMER1_A_PIN   9
  #define TIMER1_B_PIN   10
  #define TIMER1_ICP_PIN 8
  #define TIMER1_CLK_PIN 5
#elif defined(__AVR_ATmega328PB__) 
  #define TIMER1_A_PIN   9
  #define TIMER1_B_PIN   10
  #define TIMER1_ICP_PIN 8
  #define TIMER1_CLK_PIN 5
  #define TIMER3_A_PIN   0
  #define TIMER3_B_PIN   2
  #define TIMER3_ICP_PIN 25
  #define TIMER3_CLK_PIN 26
  #define TIMER4_A_PIN   1
  #define TIMER4_B_PIN   2
  #define TIMER4_ICP_PIN 23
  #define TIMER4_CLK_PIN 24

//  attiny167
//
#elif defined (__AVR_ATtiny167__)
  #define TIMER1_A_PIN   14
  #define TIMER1_B_PIN   11
  //#define TIMER1_ICP_PIN 8
  //#define TIMER1_CLK_PIN 5
  
// Sanguino
//
#elif defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644__)
  #define TIMER1_A_PIN   13
  #define TIMER1_B_PIN   12
  #define TIMER1_ICP_PIN 14
  #define TIMER1_CLK_PIN 1

// Wildfire - Wicked Devices
//
#elif defined(__AVR_ATmega1284P__) && defined(WILDFIRE_VERSION) && WILDFIRE_VERSION >= 3
  #define TIMER1_A_PIN   5   // PD5
  #define TIMER1_B_PIN   8   // PD4
  #define TIMER1_ICP_PIN 6   // PD6
  #define TIMER1_CLK_PIN 23  // PB1
  #define TIMER3_A_PIN   12  // PB6
  #define TIMER3_B_PIN   13  // PB7
  #define TIMER3_ICP_PIN 9   // PB5
  #define TIMER3_CLK_PIN 0   // PD0
#elif defined(__AVR_ATmega1284P__) && defined(WILDFIRE_VERSION) && WILDFIRE_VERSION < 3
  #define TIMER1_A_PIN   5   // PD5
  #define TIMER1_B_PIN   4   // PD4
  #define TIMER1_ICP_PIN 6   // PD6
  #define TIMER1_CLK_PIN 15  // PB1
  #define TIMER3_A_PIN   12  // PB6
  #define TIMER3_B_PIN   13  // PB7
  #define TIMER3_ICP_PIN 11  // PB5
  #define TIMER3_CLK_PIN 0   // PD0

// Mighty-1284 - Maniacbug
//
#elif defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega1284__)
  #define TIMER1_A_PIN   12  // PD5
  #define TIMER1_B_PIN   13  // PD4
  #define TIMER1_ICP_PIN 14  // PD6
  #define TIMER1_CLK_PIN 1   // PB1
  #define TIMER3_A_PIN   6   // PB6
  #define TIMER3_B_PIN   7   // PB7
  #define TIMER3_ICP_PIN 5   // PB5
  #define TIMER3_CLK_PIN 8   // PD0

#endif

#endif
/* ------------------------------------------------------------ */
#ifndef TimerOne_h_
#define TimerOne_h_

#if defined(ARDUINO) && ARDUINO >= 100
//#include "Arduino.h"
#else
//#include "WProgram.h"
#endif

//#include "config/known_16bit_timers.h"
#if defined (__AVR_ATtiny85__)
#define TIMER1_RESOLUTION 256UL  // Timer1 is 8 bit
#elif defined(__AVR__)
#define TIMER1_RESOLUTION 65536UL  // Timer1 is 16 bit
#else
#define TIMER1_RESOLUTION 65536UL  // assume 16 bits for non-AVR chips
#endif

// Placing nearly all the code in this .h file allows the functions to be
// inlined by the compiler.  In the very common case with constant values
// the compiler will perform all calculations and simply write constants
// to the hardware registers (for example, setPeriod).


class TimerOne
{

#if defined (__AVR_ATtiny85__)
  public:
    //****************************
    //  Configuration
    //****************************
    void initialize(unsigned long microseconds=1000000) __attribute__((always_inline)) {
	TCCR1 = _BV(CTC1);              //clear timer1 when it matches the value in OCR1C
	TIMSK |= _BV(OCIE1A);           //enable interrupt when OCR1A matches the timer value
	setPeriod(microseconds);
    }
    void setPeriod(unsigned long microseconds) __attribute__((always_inline)) {		
	const unsigned long cycles = microseconds * ratio;
	if (cycles < TIMER1_RESOLUTION) {
		clockSelectBits = _BV(CS10);
		pwmPeriod = cycles;
	} else
	if (cycles < TIMER1_RESOLUTION * 2UL) {
		clockSelectBits = _BV(CS11);
		pwmPeriod = cycles / 2;
	} else
	if (cycles < TIMER1_RESOLUTION * 4UL) {
		clockSelectBits = _BV(CS11) | _BV(CS10);
		pwmPeriod = cycles / 4;
	} else
	if (cycles < TIMER1_RESOLUTION * 8UL) {
		clockSelectBits = _BV(CS12);
		pwmPeriod = cycles / 8;
	} else
	if (cycles < TIMER1_RESOLUTION * 16UL) {
		clockSelectBits = _BV(CS12) | _BV(CS10);
		pwmPeriod = cycles / 16;
	} else
	if (cycles < TIMER1_RESOLUTION * 32UL) {
		clockSelectBits = _BV(CS12) | _BV(CS11);
		pwmPeriod = cycles / 32;
	} else
	if (cycles < TIMER1_RESOLUTION * 64UL) {
		clockSelectBits = _BV(CS12) | _BV(CS11) | _BV(CS10);
		pwmPeriod = cycles / 64UL;
	} else
	if (cycles < TIMER1_RESOLUTION * 128UL) {
		clockSelectBits = _BV(CS13);
		pwmPeriod = cycles / 128;
	} else
	if (cycles < TIMER1_RESOLUTION * 256UL) {
		clockSelectBits = _BV(CS13) | _BV(CS10);
		pwmPeriod = cycles / 256;
	} else
	if (cycles < TIMER1_RESOLUTION * 512UL) {
		clockSelectBits = _BV(CS13) | _BV(CS11);
		pwmPeriod = cycles / 512;
	} else
	if (cycles < TIMER1_RESOLUTION * 1024UL) {
		clockSelectBits = _BV(CS13) | _BV(CS11) | _BV(CS10);
		pwmPeriod = cycles / 1024;
	} else
	if (cycles < TIMER1_RESOLUTION * 2048UL) {
		clockSelectBits = _BV(CS13) | _BV(CS12);
		pwmPeriod = cycles / 2048;
	} else
	if (cycles < TIMER1_RESOLUTION * 4096UL) {
		clockSelectBits = _BV(CS13) | _BV(CS12) | _BV(CS10);
		pwmPeriod = cycles / 4096;
	} else
	if (cycles < TIMER1_RESOLUTION * 8192UL) {
		clockSelectBits = _BV(CS13) | _BV(CS12) | _BV(CS11);
		pwmPeriod = cycles / 8192;
	} else
	if (cycles < TIMER1_RESOLUTION * 16384UL) {
		clockSelectBits = _BV(CS13) | _BV(CS12) | _BV(CS11)  | _BV(CS10);
		pwmPeriod = cycles / 16384;
	} else {
		clockSelectBits = _BV(CS13) | _BV(CS12) | _BV(CS11)  | _BV(CS10);
		pwmPeriod = TIMER1_RESOLUTION - 1;
	}
	OCR1A = pwmPeriod;
	OCR1C = pwmPeriod;
	TCCR1 = _BV(CTC1) | clockSelectBits;
    }
	
    //****************************
    //  Run Control
    //****************************	
    void start() __attribute__((always_inline)) {
	TCCR1 = 0;
	TCNT1 = 0;		
	resume();
    }
    void stop() __attribute__((always_inline)) {
	TCCR1 = _BV(CTC1);
    }
    void restart() __attribute__((always_inline)) {
	start();
    }
    void resume() __attribute__((always_inline)) {
	TCCR1 = _BV(CTC1) | clockSelectBits;
    }
	
    //****************************
    //  PWM outputs
    //****************************
	//Not implemented yet for ATTiny85
	//TO DO
	
    //****************************
    //  Interrupt Function
    //****************************
    void attachInterrupt(void (*isr)()) __attribute__((always_inline)) {
	isrCallback = isr;
	TIMSK |= _BV(OCIE1A);
    }
    void attachInterrupt(void (*isr)(), unsigned long microseconds) __attribute__((always_inline)) {
	if(microseconds > 0) setPeriod(microseconds);
	attachInterrupt(isr);
    }
    void detachInterrupt() __attribute__((always_inline)) {
	//TIMSK = 0; // Timer 0 and Timer 1 both use TIMSK register so setting it to 0 will override settings for Timer1 as well
	TIMSK &= ~_BV(OCIE1A);
    }
    static void (*isrCallback)();
    static void isrDefaultUnused();

  private:
    static unsigned short pwmPeriod;
    static unsigned char clockSelectBits;
    static const byte ratio = (F_CPU)/ ( 1000000 );
	
#elif defined(__AVR__)

#if defined (__AVR_ATmega8__)
  //in some io definitions for older microcontrollers TIMSK is used instead of TIMSK1
  #define TIMSK1 TIMSK
#endif
	
  public:
    //****************************
    //  Configuration
    //****************************
    void initialize(unsigned long microseconds=1000000) __attribute__((always_inline)) {
	TCCR1B = _BV(WGM13);        // set mode as phase and frequency correct pwm, stop the timer
	TCCR1A = 0;                 // clear control register A 
	setPeriod(microseconds);
    }
    void setPeriod(unsigned long microseconds) __attribute__((always_inline)) {
	const unsigned long cycles = ((F_CPU/100000 * microseconds) / 20);
	if (cycles < TIMER1_RESOLUTION) {
		clockSelectBits = _BV(CS10);
		pwmPeriod = cycles;
	} else
	if (cycles < TIMER1_RESOLUTION * 8) {
		clockSelectBits = _BV(CS11);
		pwmPeriod = cycles / 8;
	} else
	if (cycles < TIMER1_RESOLUTION * 64) {
		clockSelectBits = _BV(CS11) | _BV(CS10);
		pwmPeriod = cycles / 64;
	} else
	if (cycles < TIMER1_RESOLUTION * 256) {
		clockSelectBits = _BV(CS12);
		pwmPeriod = cycles / 256;
	} else
	if (cycles < TIMER1_RESOLUTION * 1024) {
		clockSelectBits = _BV(CS12) | _BV(CS10);
		pwmPeriod = cycles / 1024;
	} else {
		clockSelectBits = _BV(CS12) | _BV(CS10);
		pwmPeriod = TIMER1_RESOLUTION - 1;
	}
	ICR1 = pwmPeriod;
	TCCR1B = _BV(WGM13) | clockSelectBits;
    }

    //****************************
    //  Run Control
    //****************************
    void start() __attribute__((always_inline)) {
	TCCR1B = 0;
	TCNT1 = 0;		// TODO: does this cause an undesired interrupt?
	resume();
    }
    void stop() __attribute__((always_inline)) {
	TCCR1B = _BV(WGM13);
    }
    void restart() __attribute__((always_inline)) {
	start();
    }
    void resume() __attribute__((always_inline)) {
	TCCR1B = _BV(WGM13) | clockSelectBits;
    }

    //****************************
    //  PWM outputs
    //****************************
    void setPwmDuty(char pin, unsigned int duty) __attribute__((always_inline)) {
	unsigned long dutyCycle = pwmPeriod;
	dutyCycle *= duty;
	dutyCycle >>= 10;
	if (pin == TIMER1_A_PIN) OCR1A = dutyCycle;
	#ifdef TIMER1_B_PIN
	else if (pin == TIMER1_B_PIN) OCR1B = dutyCycle;
	#endif
	#ifdef TIMER1_C_PIN
	else if (pin == TIMER1_C_PIN) OCR1C = dutyCycle;
	#endif
    }
    void pwm(char pin, unsigned int duty) __attribute__((always_inline)) {
	if (pin == TIMER1_A_PIN) { pinMode(TIMER1_A_PIN, OUTPUT); TCCR1A |= _BV(COM1A1); }
	#ifdef TIMER1_B_PIN
	else if (pin == TIMER1_B_PIN) { pinMode(TIMER1_B_PIN, OUTPUT); TCCR1A |= _BV(COM1B1); }
	#endif
	#ifdef TIMER1_C_PIN
	else if (pin == TIMER1_C_PIN) { pinMode(TIMER1_C_PIN, OUTPUT); TCCR1A |= _BV(COM1C1); }
	#endif
	setPwmDuty(pin, duty);
	TCCR1B = _BV(WGM13) | clockSelectBits;
    }
    void pwm(char pin, unsigned int duty, unsigned long microseconds) __attribute__((always_inline)) {
	if (microseconds > 0) setPeriod(microseconds);
	pwm(pin, duty);
    }
    void disablePwm(char pin) __attribute__((always_inline)) {
	if (pin == TIMER1_A_PIN) TCCR1A &= ~_BV(COM1A1);
	#ifdef TIMER1_B_PIN
	else if (pin == TIMER1_B_PIN) TCCR1A &= ~_BV(COM1B1);
	#endif
	#ifdef TIMER1_C_PIN
	else if (pin == TIMER1_C_PIN) TCCR1A &= ~_BV(COM1C1);
	#endif
    }

    //****************************
    //  Interrupt Function
    //****************************
	
    void attachInterrupt(void (*isr)()) __attribute__((always_inline)) {
	isrCallback = isr;
	TIMSK1 = _BV(TOIE1);
    }
    void attachInterrupt(void (*isr)(), unsigned long microseconds) __attribute__((always_inline)) {
	if(microseconds > 0) setPeriod(microseconds);
	attachInterrupt(isr);
    }
    void detachInterrupt() __attribute__((always_inline)) {
	TIMSK1 = 0;
    }
    static void (*isrCallback)();
    static void isrDefaultUnused();

  private:
    // properties
    static unsigned short pwmPeriod;
    static unsigned char clockSelectBits;






#elif defined(__arm__) && defined(TEENSYDUINO) && (defined(KINETISK) || defined(KINETISL))

#if defined(KINETISK)
#define F_TIMER F_BUS
#elif defined(KINETISL)
#define F_TIMER (F_PLL/2)
#endif

// Use only 15 bit resolution.  From K66 reference manual, 45.5.7 page 1200:
//   The CPWM pulse width (duty cycle) is determined by 2 x (CnV - CNTIN) and the
//   period is determined by 2 x (MOD - CNTIN). See the following figure. MOD must be
//   kept in the range of 0x0001 to 0x7FFF because values outside this range can produce
//   ambiguous results.
#undef TIMER1_RESOLUTION
#define TIMER1_RESOLUTION 32768

  public:
    //****************************
    //  Configuration
    //****************************
    void initialize(unsigned long microseconds=1000000) __attribute__((always_inline)) {
	setPeriod(microseconds);
    }
    void setPeriod(unsigned long microseconds) __attribute__((always_inline)) {
	const unsigned long cycles = (F_TIMER / 2000000) * microseconds;
  // A much faster if-else
  // This is like a binary serch tree and no more than 3 conditions are evaluated.
  // I haven't checked if this becomes significantly longer ASM than the simple ladder.
  // It looks very similar to the ladder tho: same # of if's and else's
 
  /*
  // This code does not work properly in all cases :(
  // https://github.com/PaulStoffregen/TimerOne/issues/17 
  if (cycles < TIMER1_RESOLUTION * 16) {
    if (cycles < TIMER1_RESOLUTION * 4) {
      if (cycles < TIMER1_RESOLUTION) {
        clockSelectBits = 0;
        pwmPeriod = cycles;
      }else{
        clockSelectBits = 1;
        pwmPeriod = cycles >> 1;
      }
    }else{
      if (cycles < TIMER1_RESOLUTION * 8) {
        clockSelectBits = 3;
        pwmPeriod = cycles >> 3;
      }else{
        clockSelectBits = 4;
        pwmPeriod = cycles >> 4;
      }
    }
  }else{
    if (cycles > TIMER1_RESOLUTION * 64) {
      if (cycles > TIMER1_RESOLUTION * 128) {
        clockSelectBits = 7;
        pwmPeriod = TIMER1_RESOLUTION - 1;
      }else{
        clockSelectBits = 7;
        pwmPeriod = cycles >> 7;
      }
    }
    else{
      if (cycles > TIMER1_RESOLUTION * 32) {
        clockSelectBits = 6;
        pwmPeriod = cycles >> 6;
      }else{
        clockSelectBits = 5;
        pwmPeriod = cycles >> 5;
      }
    }
  }
  */
	if (cycles < TIMER1_RESOLUTION) {
		clockSelectBits = 0;
		pwmPeriod = cycles;
	} else
	if (cycles < TIMER1_RESOLUTION * 2) {
		clockSelectBits = 1;
		pwmPeriod = cycles >> 1;
	} else
	if (cycles < TIMER1_RESOLUTION * 4) {
		clockSelectBits = 2;
		pwmPeriod = cycles >> 2;
	} else
	if (cycles < TIMER1_RESOLUTION * 8) {
		clockSelectBits = 3;
		pwmPeriod = cycles >> 3;
	} else
	if (cycles < TIMER1_RESOLUTION * 16) {
		clockSelectBits = 4;
		pwmPeriod = cycles >> 4;
	} else
	if (cycles < TIMER1_RESOLUTION * 32) {
		clockSelectBits = 5;
		pwmPeriod = cycles >> 5;
	} else
	if (cycles < TIMER1_RESOLUTION * 64) {
		clockSelectBits = 6;
		pwmPeriod = cycles >> 6;
	} else
	if (cycles < TIMER1_RESOLUTION * 128) {
		clockSelectBits = 7;
		pwmPeriod = cycles >> 7;
	} else {
		clockSelectBits = 7;
		pwmPeriod = TIMER1_RESOLUTION - 1;
	}

	uint32_t sc = FTM1_SC;
	FTM1_SC = 0;
	FTM1_MOD = pwmPeriod;
	FTM1_SC = FTM_SC_CLKS(1) | FTM_SC_CPWMS | clockSelectBits | (sc & FTM_SC_TOIE);
    }

    //****************************
    //  Run Control
    //****************************
    void start() __attribute__((always_inline)) {
	stop();
	FTM1_CNT = 0;
	resume();
    }
    void stop() __attribute__((always_inline)) {
	FTM1_SC = FTM1_SC & (FTM_SC_TOIE | FTM_SC_CPWMS | FTM_SC_PS(7));
    }
    void restart() __attribute__((always_inline)) {
	start();
    }
    void resume() __attribute__((always_inline)) {
	FTM1_SC = (FTM1_SC & (FTM_SC_TOIE | FTM_SC_PS(7))) | FTM_SC_CPWMS | FTM_SC_CLKS(1);
    }

    //****************************
    //  PWM outputs
    //****************************
    void setPwmDuty(char pin, unsigned int duty) __attribute__((always_inline)) {
	unsigned long dutyCycle = pwmPeriod;
	dutyCycle *= duty;
	dutyCycle >>= 10;
	if (pin == TIMER1_A_PIN) {
		FTM1_C0V = dutyCycle;
	} else if (pin == TIMER1_B_PIN) {
		FTM1_C1V = dutyCycle;
	}
    }
    void pwm(char pin, unsigned int duty) __attribute__((always_inline)) {
	setPwmDuty(pin, duty);
	if (pin == TIMER1_A_PIN) {
		*portConfigRegister(TIMER1_A_PIN) = PORT_PCR_MUX(3) | PORT_PCR_DSE | PORT_PCR_SRE;
	} else if (pin == TIMER1_B_PIN) {
		*portConfigRegister(TIMER1_B_PIN) = PORT_PCR_MUX(3) | PORT_PCR_DSE | PORT_PCR_SRE;
	}
    }
    void pwm(char pin, unsigned int duty, unsigned long microseconds) __attribute__((always_inline)) {
	if (microseconds > 0) setPeriod(microseconds);
	pwm(pin, duty);
    }
    void disablePwm(char pin) __attribute__((always_inline)) {
	if (pin == TIMER1_A_PIN) {
		*portConfigRegister(TIMER1_A_PIN) = 0;
	} else if (pin == TIMER1_B_PIN) {
		*portConfigRegister(TIMER1_B_PIN) = 0;
	}
    }

    //****************************
    //  Interrupt Function
    //****************************
    void attachInterrupt(void (*isr)()) __attribute__((always_inline)) {
	isrCallback = isr;
	FTM1_SC |= FTM_SC_TOIE;
	NVIC_ENABLE_IRQ(IRQ_FTM1);
    }
    void attachInterrupt(void (*isr)(), unsigned long microseconds) __attribute__((always_inline)) {
	if(microseconds > 0) setPeriod(microseconds);
	attachInterrupt(isr);
    }
    void detachInterrupt() __attribute__((always_inline)) {
	FTM1_SC &= ~FTM_SC_TOIE;
	NVIC_DISABLE_IRQ(IRQ_FTM1);
    }
    static void (*isrCallback)();
    static void isrDefaultUnused();

  private:
    // properties
    static unsigned short pwmPeriod;
    static unsigned char clockSelectBits;

#undef F_TIMER

#elif defined(__arm__) && defined(TEENSYDUINO) && defined(__IMXRT1062__)

  public:
    //****************************
    //  Configuration
    //****************************
    void initialize(unsigned long microseconds=1000000) __attribute__((always_inline)) {
	setPeriod(microseconds);
    }
    void setPeriod(unsigned long microseconds) __attribute__((always_inline)) {
	uint32_t period = (float)F_BUS_ACTUAL * (float)microseconds * 0.0000005f;
	uint32_t prescale = 0;
	while (period > 32767) {
		period = period >> 1;
		if (++prescale > 7) {
			prescale = 7;	// when F_BUS is 150 MHz, longest
			period = 32767; // period is 55922 us (~17.9 Hz)
			break;
		}
	}
	//Serial.printf("setPeriod, period=%u, prescale=%u\n", period, prescale);
	FLEXPWM1_FCTRL0 |= FLEXPWM_FCTRL0_FLVL(8); // logic high = fault
	FLEXPWM1_FSTS0 = 0x0008; // clear fault status
	FLEXPWM1_MCTRL |= FLEXPWM_MCTRL_CLDOK(8);
	FLEXPWM1_SM3CTRL2 = FLEXPWM_SMCTRL2_INDEP;
	FLEXPWM1_SM3CTRL = FLEXPWM_SMCTRL_HALF | FLEXPWM_SMCTRL_PRSC(prescale);
	FLEXPWM1_SM3INIT = -period;
	FLEXPWM1_SM3VAL0 = 0;
	FLEXPWM1_SM3VAL1 = period;
	FLEXPWM1_SM3VAL2 = 0;
	FLEXPWM1_SM3VAL3 = 0;
	FLEXPWM1_SM3VAL4 = 0;
	FLEXPWM1_SM3VAL5 = 0;
	FLEXPWM1_MCTRL |= FLEXPWM_MCTRL_LDOK(8) | FLEXPWM_MCTRL_RUN(8);
	pwmPeriod = period;
    }
    //****************************
    //  Run Control
    //****************************
    void start() __attribute__((always_inline)) {
	stop();
	// TODO: how to force counter back to zero?
	resume();
    }
    void stop() __attribute__((always_inline)) {
	FLEXPWM1_MCTRL &= ~FLEXPWM_MCTRL_RUN(8);
    }
    void restart() __attribute__((always_inline)) {
	start();
    }
    void resume() __attribute__((always_inline)) {
	FLEXPWM1_MCTRL |= FLEXPWM_MCTRL_RUN(8);
    }

    //****************************
    //  PWM outputs
    //****************************
    void setPwmDuty(char pin, unsigned int duty) __attribute__((always_inline)) {
	if (duty > 1023) duty = 1023;
	int dutyCycle = (pwmPeriod * duty) >> 10;
	//Serial.printf("setPwmDuty, period=%u\n", dutyCycle);
	if (pin == TIMER1_A_PIN) {
		FLEXPWM1_MCTRL |= FLEXPWM_MCTRL_CLDOK(8);
		FLEXPWM1_SM3VAL5 = dutyCycle;
		FLEXPWM1_SM3VAL4 = -dutyCycle;
		FLEXPWM1_MCTRL |= FLEXPWM_MCTRL_LDOK(8);
	} else if (pin == TIMER1_B_PIN) {
		FLEXPWM1_MCTRL |= FLEXPWM_MCTRL_CLDOK(8);
		FLEXPWM1_SM3VAL3 = dutyCycle;
		FLEXPWM1_SM3VAL2 = -dutyCycle;
		FLEXPWM1_MCTRL |= FLEXPWM_MCTRL_LDOK(8);
	}
    }
    void pwm(char pin, unsigned int duty) __attribute__((always_inline)) {
	setPwmDuty(pin, duty);
	if (pin == TIMER1_A_PIN) {
		FLEXPWM1_OUTEN |= FLEXPWM_OUTEN_PWMB_EN(8);
		IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_01 = 6; // pin 7 FLEXPWM1_PWM3_B
	} else if (pin == TIMER1_B_PIN) {
		FLEXPWM1_OUTEN |= FLEXPWM_OUTEN_PWMA_EN(8);
		IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_00 = 6; // pin 8 FLEXPWM1_PWM3_A
	}
    }
    void pwm(char pin, unsigned int duty, unsigned long microseconds) __attribute__((always_inline)) {
	if (microseconds > 0) setPeriod(microseconds);
	pwm(pin, duty);
    }
    void disablePwm(char pin) __attribute__((always_inline)) {
	if (pin == TIMER1_A_PIN) {
		IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_01 = 5; // pin 7 FLEXPWM1_PWM3_B
		FLEXPWM1_OUTEN &= ~FLEXPWM_OUTEN_PWMB_EN(8);
	} else if (pin == TIMER1_B_PIN) {
		IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_00 = 5; // pin 8 FLEXPWM1_PWM3_A
		FLEXPWM1_OUTEN &= ~FLEXPWM_OUTEN_PWMA_EN(8);
	}
    }
    //****************************
    //  Interrupt Function
    //****************************
    void attachInterrupt(void (*f)()) __attribute__((always_inline)) {
	isrCallback = f;
	attachInterruptVector(IRQ_FLEXPWM1_3, &isr);
	FLEXPWM1_SM3STS = FLEXPWM_SMSTS_RF;
	FLEXPWM1_SM3INTEN = FLEXPWM_SMINTEN_RIE;
	NVIC_ENABLE_IRQ(IRQ_FLEXPWM1_3);
    }
    void attachInterrupt(void (*f)(), unsigned long microseconds) __attribute__((always_inline)) {
	if(microseconds > 0) setPeriod(microseconds);
	attachInterrupt(f);
    }
    void detachInterrupt() __attribute__((always_inline)) {
	NVIC_DISABLE_IRQ(IRQ_FLEXPWM1_3);
	FLEXPWM1_SM3INTEN = 0;
    }
    static void isr(void);
    static void (*isrCallback)();
    static void isrDefaultUnused();

  private:
    // properties
    static unsigned short pwmPeriod;
    static unsigned char clockSelectBits;

#endif
};

extern TimerOne Timer1;

#endif
/* ------------------------------------------------------------ */
TimerOne Timer1;              // preinstatiate

unsigned short TimerOne::pwmPeriod = 0;
unsigned char TimerOne::clockSelectBits = 0;
void (*TimerOne::isrCallback)() = TimerOne::isrDefaultUnused;

// interrupt service routine that wraps a user defined function supplied by attachInterrupt
#if defined (__AVR_ATtiny85__)
ISR(TIMER1_COMPA_vect)
{
  Timer1.isrCallback();
}
#elif defined(__AVR__)
ISR(TIMER1_OVF_vect)
{
  Timer1.isrCallback();
}
#elif defined(__arm__) && defined(TEENSYDUINO) && (defined(KINETISK) || defined(KINETISL))
void ftm1_isr(void)
{
  uint32_t sc = FTM1_SC;
  #ifdef KINETISL
  if (sc & 0x80) FTM1_SC = sc;
  #else
  if (sc & 0x80) FTM1_SC = sc & 0x7F;
  #endif
  Timer1.isrCallback();
}
#elif defined(__arm__) && defined(TEENSYDUINO) && defined(__IMXRT1062__)
void TimerOne::isr(void)
{
  FLEXPWM1_SM3STS = FLEXPWM_SMSTS_RF;
  Timer1.isrCallback();
}

#endif

void TimerOne::isrDefaultUnused()
{
}








/* ------------------------------------------------------------ */
// Programador: Cristian Sánchez Rodríguez

// Asignatura: Sistemas empotrados y de tiempo real

// Descripción: Este sistema simula una alarma la cual se enciende
//				pulsando un botón.
//
//				Una vez encendida, si detecta cambios de temperatura o 
//				movimiento, entra en un estado de alerta donde parpadea
//				un led, hasta que se pulsa un botón.
/* ------------------------------------------------------------ */

// -- VARIABLES Y LIBRERIAS -- //
#include <LiquidCrystal.h>
enum AlarmState{
  OFF,
  DETECTING,
  INTRUDER,
  OFF_TO_DET,
  DET_TO_INT,
  INT_TO_DET,
  DET_TO_OFF
};

// Pines que van a usarse
const int PIRpin = 3, TMPpin = A0, LCD_RSpin = 12,
          LCD_Epin = 11, LCD_D4pin = 5, LCD_D3pin = 4,
          LCD_D2pin = 8, LCD_D1pin = 7, LED1pin = 10,
		  BUTTONpin = 2, REDpin = 9, GREENpin = 6,
          inputPINS[] = {PIRpin, BUTTONpin, TMPpin},
          outputPINS[] = {LED1pin, REDpin, GREENpin};
          
int pir_value, state, switcher;
float tmp_value = 0.0, previous_tmp = 0.0;

// Variables de las ISR
volatile float tmp_read = 0.0;
volatile int led_state = LOW, move_detected = LOW;
volatile int button_state = LOW;

// LCD
LiquidCrystal lcd(LCD_RSpin, LCD_Epin, 
                  LCD_D4pin, LCD_D3pin, 
                  LCD_D2pin, LCD_D1pin);

// -- ISR -- //

// Aquí se define el funcionamiento de las distintas interrupciones,
// tanto software, como hardware, que van a estar presentes en 
// nuestro sistema de alarma.

void PIR_ISR()
// ISR del sensor de movimiento que modifica el valor a su opuesto
// frente a cualquier cambio.
{
  noInterrupts();  
  move_detected = !move_detected;
  interrupts();
}

void BUTTON_ISR()
// ISR del botón, cada vez que se detecta un flanco de subida,
// cambia el estado del botón.
{
  noInterrupts();  
  button_state = !button_state;
  interrupts();
}

void LED_ISR()
// ISR del led que parpadea, cambia el estado del led cada vez que
// se ejecuta, es decir cada 500 ms.
{
  noInterrupts();
  led_state = !led_state;
  digitalWrite(LED1pin, led_state);
  interrupts();
}

void TMP_ISR()
// ISR del sensor de temperatura, toma una medida cada 2 s.
{
  noInterrupts();  
  tmp_read = analogRead(TMPpin);
  interrupts();
}

// -- MÉTODOS GENERALES -- //
void lcd_display(const int STATE)
// Se encarga de gestionar el display del LCD en función del 
// estado que reciba como parámetro.
{
  switch (STATE){
    case (OFF):
      lcd.print("    ALARM OFF   ");
      lcd.setCursor(0, 1);
      lcd.print("");
      lcd.setCursor(0, 0);
      break;
    
   	case (DETECTING):
      lcd.print("Movimiento: NO");
      lcd.setCursor(0, 1);
      lcd.print("Temperatura:");
      lcd.print(tmp_value);
      lcd.setCursor(0, 0);
      break;
    
    case (OFF_TO_DET):
      lcd.clear();
      lcd.print("    ALARM ON   ");
      lcd.setCursor(0, 1);
      lcd.print("");
      lcd.setCursor(0, 0);
      delay(1000);
      break;
    
    case (DET_TO_INT):
      lcd.print("Movimiento: SI");
      lcd.setCursor(0, 1);
      lcd.print("Temperatura:");
      lcd.print(tmp_value);
      lcd.setCursor(0, 0);
      break;
    
    case (DET_TO_OFF):
      lcd.clear();
      lcd.print("    ALARM OFF   ");
      lcd.setCursor(0, 1);
      lcd.print("");
      lcd.setCursor(0, 0);
      break;
  }
}

// -- SETUP -- //
void setup()
{
  // Inicialización de la comunicación, lcd y pines
  Serial.begin(9600);  
  lcd.begin(16, 2);  
  for (int i = 0; i<sizeof(inputPINS); i++)
    pinMode(inputPINS[i], INPUT);
  for (int i = 0; i<sizeof(outputPINS); i++)
    pinMode(outputPINS[i], OUTPUT);
  
  // Inicialización de variables para el estado primero del sistema
  state = OFF; 
  analogWrite(REDpin, 255);
  analogWrite(GREENpin, 0);
  tmp_read = analogRead(TMPpin);
  tmp_value = (tmp_read * (500.0/1023.0)) - 50.0;
  switcher = 0; // Sirve para la trazabilidad por la salida serial, para imprimir 1 vez
  
  // Interrupción hardware para la detección de movimiento con el PIR y el botón
  attachInterrupt(digitalPinToInterrupt(PIRpin), PIR_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTONpin), BUTTON_ISR, RISING);
}

// -- LOOP -- //
void loop()
{  
  // - MAQUINA DE ESTADOS - //  
  // 	> OFF 		-> alarma apagada
  //	> DETECTING	-> alarma obteniendo info de la temperatura y del movimiento
  //	> INTRUDER	-> alarma en estado de alerta, tras haber detectado algo  
  switch (state){
    case (OFF):
    	// Traza...
    	if (switcher == 0){
          Serial.println("STATE: Off");
          switcher = -1;
        }      	
    
    	lcd_display(OFF);
    
    	if (button_state){
          // Transición OFF --> DETECTING
          button_state = LOW;
          Serial.println("(Transition) Off --> Detecting");
          
          lcd_display(OFF_TO_DET);
          
          state = DETECTING;
          analogWrite(REDpin, 0);
    	  analogWrite(GREENpin, 255);
          switcher = 1;
          
          delay(1000);
          
          // Activamos interrupción del sensor de temperatura (2s)
          Timer1.detachInterrupt();
          Timer1.initialize(2000000);
  		  Timer1.attachInterrupt(TMP_ISR);
          
          lcd.clear();          
        } 	
    	break;
    case (DETECTING):
    	// Traza...
    	if (switcher == 1){
          Serial.println("STATE: Detecting");
          switcher = -1;
        }
    
    	if (button_state){
          // Transición DETECTING --> OFF
          button_state = LOW;
          Serial.println("(Transition) Detecting --> Off");
          
          lcd_display(DET_TO_OFF);
          
          state = OFF;
          analogWrite(REDpin, 255);
    	  analogWrite(GREENpin, 0);
          switcher = 0;
        }else{
          // Comparación del valor de temperatura anterior y actual
          previous_tmp = tmp_value;
          tmp_value = (tmp_read * (500.0/1023.0)) - 50.0;
          
          // Si la temperatura aumenta más de 5º o se detecta movimiento...
          if (((tmp_value - previous_tmp) > 5.0)||(move_detected)){
            // Transición DETECTING --> INTRUDER
            Serial.println("(Transition) Detecting --> Intruder");
            
            lcd_display(DET_TO_INT);
            
            state = INTRUDER;
            switcher = 2;
            
            // Activamos interrupción del led parpadeando (0'5s)
            Timer1.detachInterrupt();
            Timer1.initialize(500000);
            Timer1.attachInterrupt(LED_ISR);                 
          }else{
            lcd_display(DETECTING);
          }            
        }
    	break;
    case (INTRUDER):
    	// Traza...
    	if (switcher == 2){
          Serial.println("STATE: Intruder");
          switcher = -1;
        }

        if (button_state){
          // Transición INTRUDER --> DETECTING 
          button_state = LOW;
          Serial.println("(Transition) Intruder --> Detecting");
          
          state = DETECTING;
          switcher = 1;
          
          // Retornamos el led a su estado inicial (apagado) para transicionar.
          if (led_state){
            led_state = LOW;
            digitalWrite(LED1pin, led_state);
          }
          
          // Activamos interrupción del sensor de temperatura (2s)
          Timer1.detachInterrupt();
          Timer1.initialize(2000000);
  		  Timer1.attachInterrupt(TMP_ISR);
        }
    	break;
    default:
    	// Gestión de fallos inesperados.
    	Serial.println("ERROR, something unexpected happened...\n");
  }
  delay(30);
}
