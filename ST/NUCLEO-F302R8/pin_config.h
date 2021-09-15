// board NUCLEO-F302R8
#include "../main.h"
void init_led_board_portb(void);
void led_board_toggle(void);
void init_pa3_output(void); 
void init_pa0_output(void);
void toggle_pa0(void);
void led_pa3_toggle(void);
void init_board_button1(void);

void board_led_toggle_bsrr(void);
uint8_t board_button_state(void);

void init_port_a_clock(void);
void init_port_b_clock(void);
void init_port_c_clock(void);
void init_port_d_clock(void);