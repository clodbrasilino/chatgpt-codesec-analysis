#include <stdio.h>
#include <stdlib.h>

unsigned long long convert_decimal_to_octal(unsigned int decimal);

unsigned long long convert_decimal_to_octal(unsigned int decimal) {
    unsigned long long octal_number = 0;
    unsigned long long place_value = 1;

    while (decimal > 0) {
        octal_number += (decimal % 8) * place_value;
        decimal /= 8;
        place_value *= 10;
    }

    return octal_number;
}

int main(void) {
    unsigned int decimal_value = 0;

    if (scanf("%u", &decimal_value) != 1) {
        return EXIT_FAILURE;
    }

    unsigned long long octal_value = convert_decimal_to_octal(decimal_value);

    printf("%llu\n", octal_value);

    return EXIT_SUCCESS;
}