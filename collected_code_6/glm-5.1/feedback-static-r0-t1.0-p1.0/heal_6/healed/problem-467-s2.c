#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void decimal_to_octal(int decimal, char *buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return;
    }

    if (decimal == 0) {
        if (size > 1) {
            buffer[0] = '0';
            buffer[1] = '\0';
        } else {
            buffer[0] = '\0';
        }
        return;
    }

    int negative = 0;
    unsigned int num;

    if (decimal < 0) {
        negative = 1;
        num = (unsigned int)(-(decimal + 1)) + 1;
    } else {
        num = (unsigned int)decimal;
    }

    char temp[sizeof(int) * CHAR_BIT / 3 + 2];
    size_t i = 0;

    while (num > 0) {
        if (i >= sizeof(temp) / sizeof(temp[0])) {
            break;
        }
        temp[i] = (num % 8) + '0';
        i++;
        num /= 8;
    }

    size_t required_size = i + (size_t)negative + 1;

    if (required_size > size) {
        buffer[0] = '\0';
        return;
    }

    size_t buffer_index = 0;

    if (negative) {
        buffer[buffer_index++] = '-';
    }

    while (i > 0) {
        buffer[buffer_index++] = temp[--i];
    }

    buffer[buffer_index] = '\0';
}

int main(void) {
    int number;
    
    if (scanf("%d", &number) != 1) {
        return EXIT_FAILURE;
    }

    char octal_str[sizeof(int) * CHAR_BIT / 3 + 3];
    decimal_to_octal(number, octal_str, sizeof(octal_str) / sizeof(octal_str[0]));
    
    if (octal_str[0] != '\0') {
        printf("%s\n", octal_str);
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}