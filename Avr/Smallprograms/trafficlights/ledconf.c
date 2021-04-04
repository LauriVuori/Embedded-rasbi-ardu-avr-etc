#define F_CPU 10000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
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


#define FLAGS 4
#define CARTKFLAG 0
#define CARTTFLAG 1
#define WALTKFLAG 2
#define WALTTFLAG 3



uint8_t buttonFlags[FLAGS] = {0};
volatile uint8_t time = 0;
void Timer_init(void);
void init_leds(void);
void turnOffLeds(void);
void checkButtons(void);
void test(void);
#define DELAY 200
int main(void) {

	init_leds();
	Timer_init();
	
	while (1) {
        test();
	}
}

void test(void) {
    if (buttonFlags[CARTKFLAG] == 1) {
        PORTB |= TKCREDB;
        _delay_ms(DELAY);
        PORTB ^= TKCREDB;
        PORTB |= TKCYELB;
        _delay_ms(DELAY);
        PORTB ^= TKCYELB;
        PORTB |= TKCGREB;
        _delay_ms(DELAY);
        PORTB ^= TKCGREB;
        _delay_ms(DELAY);
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
	//turnOffLeds();
}




void checkButtons() {
	// CARTKFLAG = 0
	if (~PINB & TKCBUTB) {
		buttonFlags[CARTKFLAG] = 1;
	}
	// CARTTFLAG = 1
	if (~PIND & TTCBUTD) {
		buttonFlags[CARTTFLAG] = 1;
	}
    // WALTKFLAG = 2
	if (~PIND & TKWBUTD) {
        buttonFlags[WALTKFLAG] = 1;
    }
    // TTWBUTD = 3
	if (~PIND & TTWBUTD) {
        buttonFlags[WALTTFLAG] = 1;
    }
	
}

ISR(TIMER1_OVF_vect) {
	time ++;
	TCNT1 = 200;
	checkButtons();
}

void Timer_init(void) {
	// timer start, jakoluku CLK/64
	// TCCR1B |= (1<<CS11) | (1<<CS10); // cs12, cs 11, cs 10 = tccr1b
	
	TCCR1B |= (1 << CS10); // 256 10mHz/ 256 = 39062.5
	TIMSK |= 1 << TOIE1;
	TCNT1 = 200;
	sei();
	//TCCR0 = 4;
	// TOIE1, timer1 overflow interrupt enable
}


void turnOffLeds() {
	PORTB = 0x00 | (TKCBUTB);
	PORTD = 0x00 | (TTCBUTD | TKWBUTD | TTWBUTD);
	_delay_ms(20);
}


void init_leds(){
	DDRB = 0xFF ^ TKCBUTB;
	DDRD = 0xFF ^ (TTCBUTD | TKWBUTD | TTWBUTD) ;
	turnOffLeds();
}