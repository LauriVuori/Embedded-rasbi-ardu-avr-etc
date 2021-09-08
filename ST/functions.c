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


