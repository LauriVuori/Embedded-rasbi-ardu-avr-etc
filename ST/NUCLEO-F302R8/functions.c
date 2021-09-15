#include "functions.h"

void format_to_binary(uint32_t n) {
    uint32_t i;
    uint8_t counter = 1, current = 0;
    uint8_t binary_form[40];
    // binary_form[41] = '\0';
    for (i = 1 << 31; i > 0; i = i / 2) {
        if (n&i) {
            binary_form[current] = '1';
        }
        else {
            binary_form[current] = '0';
        }

        if ((counter % 4 == 0)) {
            current++;
            binary_form[current] = ' ';
        }
        current++;
        counter++;
    }
    binary_form[current] = '\0';
}

void format_to_binary_usart2(uint32_t n) {
    uint32_t i;
    uint8_t counter = 1, current = 0;
    uint8_t binary_form[45];
    // binary_form[41] = '\0';
    for (i = 1 << 31; i > 0; i = i / 2) {
        if (n&i) {
            binary_form[current] = '1';
        }
        else {
            binary_form[current] = '0';
        }

        if ((counter % 4 == 0)) {
            current++;
            binary_form[current] = ' ';
        }
        current++;
        counter++;
    }
    binary_form[current] = '\n';
    binary_form[current+1] = '\0';
    USART2_write_string(binary_form);
}

void uint8_to_char_array(uint8_t uInteger, uint8_t * dest_array) {
    // needs atleast [6] array
	uint8_t* ptr_to_buffer;
	uint8_t int_buffer [5];

	ptr_to_buffer = &int_buffer[4];        // Point to buffer end
    *ptr_to_buffer = 0;
	do {
        // make characters, (uInteger % 10) = 5, 5 + '0' = 53=='5'
        *--ptr_to_buffer = (uInteger % 10) + '0';
    }while (uInteger /= 10 );
	while (*ptr_to_buffer) {
        *dest_array = *ptr_to_buffer;
        dest_array++;
        ptr_to_buffer++;
	}
    // end char
    *dest_array = '\0';
}

void uint16_to_char_array(uint16_t uInteger, uint8_t * dest_array) {
	// needs atleast [6] array
	uint8_t* ptr_to_buffer;
	uint8_t int_buffer [11];

	ptr_to_buffer = &int_buffer[10];        // Point to buffer end
	*ptr_to_buffer = 0;
	do {
		// make characters, (uInteger % 10) = 5, 5 + '0' = 53=='5'
		*--ptr_to_buffer = (uInteger % 10) + '0';
	}while (uInteger /= 10 );

	while (*ptr_to_buffer) {
		*dest_array = *ptr_to_buffer;
		dest_array++;
		ptr_to_buffer++;
	}
	// end char
	*dest_array = '\0';
}
void uint32_to_char_array(uint32_t uInteger, uint8_t * dest_array) {
    // needs atleast [6] array
	uint8_t* ptr_to_buffer;
	uint8_t int_buffer [12];

	ptr_to_buffer = &int_buffer[11];        // Point to buffer end
    *ptr_to_buffer = 0;
    do {
        // make characters, (uInteger % 10) = 5, 5 + '0' = 53=='5'
        *--ptr_to_buffer = (uInteger % 10) + '0';
    }while (uInteger /= 10 );

	while (*ptr_to_buffer) {
        *dest_array = *ptr_to_buffer;
        dest_array++;
        ptr_to_buffer++;
	}
    // end char
    *dest_array = '\0';
}
