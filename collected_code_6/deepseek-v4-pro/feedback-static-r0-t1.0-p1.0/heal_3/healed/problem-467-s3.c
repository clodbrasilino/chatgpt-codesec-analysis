#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char *decimal_to_octal(int decimal) {
    char *octal = malloc(12 * sizeof(char));
    if (octal == NULL) {
        return NULL;
    }

    if (decimal == 0) {
        octal[0] = '0';
        octal[1] = '\0';
        return octal;
    }

    int is_negative = 0;
    unsigned int num;
    if (decimal < 0) {
        is_negative = 1;
        num = (unsigned int)(-(long long)decimal);
    } else {
        num = (unsigned int)decimal;
    }

    char temp[12];
    size_t i = 0;
    while (num > 0 && i < sizeof(temp) - 1) {
        temp[i++] = '0' + (num % 8);
        num /= 8;
    }
    temp[i] = '\0';

    size_t index = 0;
    if (is_negative) {
        octal[index++] = '-';
    }

    size_t max_digits = sizeof(temp) - 1 - is_negative;
    size_t digits_to_copy = i;
    if (digits_to_copy > max_digits) {
        digits_to_copy = max_digits;
    }

    for (size_t j = digits_to_copy; j > 0; j--) {
        octal[index++] = temp[j - 1];
    }
    octal[index] = '\0';

    return octal;
}

int main(void) {
    int test_values[] = {0, 8, 64, -8, -64, 123, -123, 100, -100};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *result = decimal_to_octal(test_values[i]);
        if (result != NULL) {
            printf("Decimal: %d -> Octal: %s\n", test_values[i], result);
            free(result);
        } else {
            printf("Memory allocation failed for decimal: %d\n", test_values[i]);
        }
    }

    return 0;
}