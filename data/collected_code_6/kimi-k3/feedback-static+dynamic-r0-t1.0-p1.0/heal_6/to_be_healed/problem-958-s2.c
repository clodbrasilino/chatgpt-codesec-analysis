#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

void int_to_roman(int num, char *result, size_t size) {
    if (result == NULL || size == 0) {
        return;
    }

    if (num <= 0 || num > 3999 || size < 16) {
        result[0] = '\0';
        return;
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
                return;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, roman_numerals[i], len);
            offset += len;
            remaining -= len;
            num -= values[i];
        }
    }
    result[offset] = '\0';
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char roman[16];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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

    int_to_roman((int)number, roman, sizeof(roman));

    if (roman[0] == '\0') {
        fprintf(stderr, "Conversion failed.\n");
        return EXIT_FAILURE;
    }

    printf("Roman numeral: %s\n", roman);
    return EXIT_SUCCESS;
}