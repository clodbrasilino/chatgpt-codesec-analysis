#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int romanToInt(const char *s) {
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const size_t len_values = sizeof(values) / sizeof(values[0]);
    const char *p = s;
    int result = 0;

    while (*p) {
        for (size_t i = 0; i < len_values; ++i) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(roman[i]);
            if (strncmp(p, roman[i], len) == 0) {
                result += values[i];
                p += len;
                break;
            }
        }
    }

    return result;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[16] = "";
    printf("Enter a Roman numeral: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t input_len = strlen(input);
        if (input_len > 15 || input_len == 0) {
            fprintf(stderr, "Input too long or empty\n");
            return EXIT_FAILURE;
        }
        for (size_t i = 0; i < input_len; ++i) {
            if (input[i] != 'I' && input[i] != 'V' && input[i] != 'X' && input[i] != 'L' && 
                input[i] != 'C' && input[i] != 'D' && input[i] != 'M') {
                fprintf(stderr, "Invalid characters in input\n");
                return EXIT_FAILURE;
            }
        }
        int output = romanToInt(input);
        printf("The integer value is: %d\n", output);
    } else {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    return 0;
}