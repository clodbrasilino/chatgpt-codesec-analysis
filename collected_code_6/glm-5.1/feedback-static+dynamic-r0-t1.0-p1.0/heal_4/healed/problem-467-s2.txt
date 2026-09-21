#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

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

    char temp[sizeof(unsigned int) * CHAR_BIT + 1];
    int i = 0;

    while (num > 0) {
        temp[i++] = (num % 8) + '0';
        num /= 8;
    }

    size_t required_size = (size_t)i + negative + 1;

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

    size_t max_octal_len = (sizeof(unsigned int) * CHAR_BIT + 2) / 3 + 1 + 1;
    char *octal_str = malloc(max_octal_len);
    if (octal_str == NULL) {
        return EXIT_FAILURE;
    }

    decimal_to_octal(number, octal_str, max_octal_len);
    
    if (octal_str[0] != '\0') {
        printf("%s\n", octal_str);
        free(octal_str);
        return EXIT_SUCCESS;
    }

    free(octal_str);
    return EXIT_FAILURE;
}