#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int int_to_roman(int num, char *result, size_t size) {
    if (result == NULL || size == 0) {
        return -1;
    }

    if (num <= 0 || num > 3999 || size < 16) {
        result[0] = '\0';
        return -1;
    }

    static const char *const roman_numerals[] = {
        "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"
    };
    static const int values[] = {
        1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
    };
    static const size_t lengths[] = {
        1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1
    };

    result[0] = '\0';
    size_t offset = 0;
    size_t remaining = size - 1;

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            size_t len = lengths[i];
            if (len > remaining) {
                result[0] = '\0';
                return -1;
            }
            memcpy(result + offset, roman_numerals[i], len);
            offset += len;
            remaining -= len;
            num -= values[i];
        }
    }
    result[offset] = '\0';
    return 0;
}

int main(void) {
    char roman[16];
    char input[64];
    long number;
    char *endptr;

    printf("Enter an integer (1-3999): ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtol(input, &endptr, 10);
    
    if (errno != 0 || endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (number < 1 || number > 3999) {
        fprintf(stderr, "Number out of range (1-3999).\n");
        return EXIT_FAILURE;
    }

    if (int_to_roman((int)number, roman, sizeof(roman)) != 0) {
        fprintf(stderr, "Conversion failed.\n");
        return EXIT_FAILURE;
    }

    printf("Roman numeral: %s\n", roman);
    return EXIT_SUCCESS;
}