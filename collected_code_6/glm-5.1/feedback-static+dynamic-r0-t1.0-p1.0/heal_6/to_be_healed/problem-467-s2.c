#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
/* Possible weaknesses found:
 *  include '<string.h>' or provide a declaration of 'memmove'
 */
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

    size_t pos = size;
    buffer[--pos] = '\0';

    while (num > 0) {
        if (pos == 0) {
            buffer[0] = '\0';
            return;
        }
        buffer[--pos] = (num % 8) + '0';
        num /= 8;
    }

    if (negative) {
        if (pos == 0) {
            buffer[0] = '\0';
            return;
        }
        buffer[--pos] = '-';
    }

    size_t len = size - pos;
    /* Possible weaknesses found:
     *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'memmove'
     *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    memmove(buffer, buffer + pos, len);
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