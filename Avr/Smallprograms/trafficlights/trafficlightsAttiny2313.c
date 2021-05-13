#define F_CPU 10000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define ATTINY
#ifdef ATTINY
//tietotie
// walker lights
#define TTWREDB 0x02 //pb1
#define TTWGREB 0x20 //pb5

// car lights
#define TTCREDD 0x02 //pa1
#define TTCYELD 0x40 //pa6
#define TTCGRED 0x04 //pa2
//car button
#define TTCBUTD 0x20 //pa5
#define TTWBUTD 0x01 // pa0
// tietokatu LeftRight
// walker lights
#define TKWREDD 0x08 // pa3
#define TKWGREB 0x80 // pa7 attiny2313 there is no pd7 -> PB7
// Car lights
#define TKCYELB 0x04 //pb2
#define TKCREDB 0x08 //pb3
#define TKCGREB 0x40 //pb6

//walker push button
#define TKWBUTD 0x10 //pa 4
//car push button
#define TKCBUTB 0x01

#define FLAGS 5
#define CARTKFLAG 0
#define CARTTFLAG 1
#define WALTKFLAG 2
#define WALTTFLAG 3
#define NOTRAFFIC 4
#define TRAFFICDELAY 150 // use 200*52 = 10400 ms


volatile uint8_t noTrafficTimer = 0;
volatile uint8_t buttonFlags[FLAGS] = {0};
volatile uint8_t time = 0;
void Timer_init(void);
void init_leds(void);
void turnOffLeds(void);
void checkButtons(void);
void test(void);
void wait52ms (uint8_t wait);
void checkTraffic(void);
void yellowLights(void);
void carttLights(void);
void cartkLights(void);
void turnOnReds();
#define DELAY 200
int main(void) {
	Timer_init();
	init_leds();
	uint8_t switchRoads = 0;
	// uint8_t startTime = 0;
	// startTime = time;
	// for (int i = 0; i <= wait; i++) {
	//     i = time-startTime;
	// }

	while (1) {
        if (buttonFlags[CARTKFLAG] == 1) {
            cartkLights();
            buttonFlags[NOTRAFFIC] = 0;
            noTrafficTimer = 0;
            buttonFlags[CARTKFLAG] = 0;
            switchRoads = 1;
        }
        else if (buttonFlags[CARTTFLAG] == 1) {
            carttLights();
            buttonFlags[NOTRAFFIC] = 0;
            buttonFlags[CARTTFLAG] = 0;
            noTrafficTimer = 0;
            switchRoads = 2;
        }
        else if (buttonFlags[WALTKFLAG] == 1) {
            waltkLights();
            buttonFlags[NOTRAFFIC] = 0;
            buttonFlags[WALTKFLAG] = 0;
            noTrafficTimer = 0;
        }
        else if (buttonFlags[WALTTFLAG] == 1) {
            walttLights();
            buttonFlags[NOTRAFFIC] = 0;
            buttonFlags[WALTTFLAG] = 0;
            noTrafficTimer = 0;
        }
        else {
            if (buttonFlags[NOTRAFFIC] == 1) {
                yellowLights();
            }
            else {
                if (switchRoads % 2 == 0) {
                    cartkLights();
                }
                else {
                    carttLights();
                }
                switchRoads++;
            }
        }
    }

		// if (time - noTrafficTimer >= 100) {
}

void walttLights(void) {
	turnOnReds();
	PORTB ^= TTWREDB;
	PORTB |= TTWGREB;
	wait52ms(30);
	turnOnReds();
}
void waltkLights(void) {
	turnOnReds();
	PORTD ^= TKWREDD;
	PORTB |= TKWGREB;
	wait52ms(30);
	turnOnReds();
}

void carttLights(void) {
	turnOnReds();
	PORTD |= TTCREDD;
	wait52ms(20);
	PORTD |= TTCYELD;
	wait52ms(20);
	PORTD ^= TTCREDD;
	PORTD ^= TTCYELD;
	PORTD |= TTCGRED;
	wait52ms(30);
	PORTD ^= TTCGRED;
	PORTD |= TTCYELD;
	wait52ms(20);
	turnOnReds();
}
void cartkLights(void) {
	turnOnReds();
	PORTB |= TKCREDB;
	wait52ms(20);
	PORTB |= TKCYELB;
	wait52ms(20);
	PORTB ^= TKCREDB;
	PORTB ^= TKCYELB;
	PORTB |= TKCGREB;
	wait52ms(30);
	PORTB ^= TKCGREB;
	PORTB |= TKCYELB;
	wait52ms(20);
	PORTB ^= TKCYELB;
	turnOnReds();
}


void yellowLights(void){
	turnOffLeds();
	PORTB |= TKCYELB;
	PORTD |= TTCYELD;
	wait52ms(10);
	PORTB ^= TKCYELB;
	PORTD ^= TTCYELD;
	wait52ms(10);
}

void wait52ms (uint8_t wait) {
	uint8_t difference = 0;
	uint8_t starttime = time;
	while (difference <= wait){
		difference = time-starttime;
	}
}

void test(void) {
	if (buttonFlags[CARTKFLAG] == 1) {
		PORTB |= TKCREDB;
		//_delay_ms(DELAY);
		wait52ms(20);
		PORTB ^= TKCREDB;
		PORTB |= TKCYELB;
		// _delay_ms(DELAY);
		wait52ms(20);
		PORTB ^= TKCYELB;
		PORTB |= TKCGREB;
		// _delay_ms(DELAY);
		wait52ms(25);
		PORTB ^= TKCGREB;
		// _delay_ms(DELAY);
		buttonFlags[CARTKFLAG] = 0;
	}
	if (buttonFlags[CARTTFLAG] == 1) {
		PORTD |= TTCREDD;
		_delay_ms(DELAY);
		PORTD ^= TTCREDD;
		PORTD |= TTCYELD;
		_delay_ms(DELAY);
		PORTD ^= TTCYELD;
		PORTD |= TTCGRED;
		_delay_ms(DELAY);
		PORTD ^= TTCGRED;
		buttonFlags[CARTTFLAG] = 0;
	}

	if (buttonFlags[WALTKFLAG] == 1) {
		PORTD |= TKWREDD;
		_delay_ms(DELAY);
		PORTD ^= TKWREDD;
		PORTB |= TKWGREB;
		_delay_ms(DELAY);
		PORTB ^= TKWGREB;
		buttonFlags[WALTKFLAG] = 0;
	}
	if (buttonFlags[WALTTFLAG] == 1) {
		PORTB |= TTWREDB;
		_delay_ms(DELAY);
		PORTB ^= TTWREDB;
		PORTB |= TTWGREB;
		_delay_ms(DELAY);
		PORTB ^= TTWGREB;
		buttonFlags[WALTTFLAG] = 0;
	}
	// if (buttonFlags[NOTRAFFIC] == 1){
	// 	PORTB |= TKCYELB;
	// 	PORTD |= TTCYELD;
	// 	wait52ms(10);
	// 	PORTB ^= TKCYELB;
	// 	PORTD ^= TTCYELD;
	// 	wait52ms(10);
	// }
}




void checkButtons() {
	// CARTKFLAG = 0
	if (~PINB & TKCBUTB) {
		buttonFlags[CARTKFLAG] = 1;
	}
	// CARTTFLAG = 1
	if (~PIND & TTCBUTD) {
		buttonFlags[CARTTFLAG] = 1;
		buttonFlags[NOTRAFFIC] = 0;
		noTrafficTimer = 0;
	}
	// WALTKFLAG = 2
	if (~PIND & TKWBUTD) {
		buttonFlags[WALTKFLAG] = 1;
		buttonFlags[NOTRAFFIC] = 0;
		noTrafficTimer = 0;
	}
	// TTWBUTD = 3
	if (~PIND & TTWBUTD) {
		buttonFlags[WALTTFLAG] = 1;
		buttonFlags[NOTRAFFIC] = 0;
		noTrafficTimer = 0;
	}
	
}

ISR(TIMER1_OVF_vect) {
	time ++;
	TCNT1 = 4835;
	checkButtons();
	checkTraffic();
}
void checkTraffic(void) {
	if (buttonFlags[NOTRAFFIC] == 0) {
		if (noTrafficTimer <= TRAFFICDELAY) {
			noTrafficTimer++;
		}
		else{
			buttonFlags[NOTRAFFIC] = 1;
		}
		
	}
	// difference = time - noTrafficTimer;
}
void Timer_init(void) {
	// 1 250 000 / 65 535 = 19.073 times in second
	// start timer on 4835 -> 19 times
	// 52.63 ms per overflow
	TCCR1B |= (1 << CS11); // 8 10mHz/ 8 = 1 250 000
	TIMSK |= 1 << TOIE1;
	TCNT1 = 4835;
	sei();
	// TOIE1, timer1 overflow interrupt enable
}


void turnOffLeds() {
	PORTB = 0x00 | (TKCBUTB);
	PORTD = 0x00 | (TTCBUTD | TKWBUTD | TTWBUTD);
	wait52ms(1);
}

void turnOnReds() {
	PORTB = 0x00 | (TKCBUTB) | (TKCREDB) | (TTWREDB) ;
	PORTD = 0x00 | (TTCBUTD | TKWBUTD | TTWBUTD) | (TKWREDD) | (TTCREDD);
	wait52ms(1);
}

void init_leds(){
	DDRB = 0xFF ^ TKCBUTB;
	DDRD = 0xFF ^ (TTCBUTD | TKWBUTD | TTWBUTD) ;
	turnOnReds();
}