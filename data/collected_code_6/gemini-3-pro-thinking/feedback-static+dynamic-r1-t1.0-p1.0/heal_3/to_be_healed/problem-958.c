#include <stdio.h>
#include <stddef.h>

int int_to_roman(int num, char *buffer, size_t buffer_size) {
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    size_t pos = 0;

    if (num < 1 || num > 3999 || buffer == NULL || buffer_size < 16) {
        return -1;
    }

    buffer[0] = '\0';

    for (size_t i = 0; i < 13; i++) {
        while (num >= values[i]) {
            int written = snprintf(buffer + pos, buffer_size - pos, "%s", symbols[i]);
            
            if (written < 0 || (size_t)written >= buffer_size - pos) {
                return -1;
            }
            
            pos += written;
            num -= values[i];
        }
    }

    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char roman_buffer[64];
    const int test_cases[] = {1, 4, 9, 58, 1994, 3999, -1, 4000, 0};
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_cases; i++) {
        int current_num = test_cases[i];
        
        if (int_to_roman(current_num, roman_buffer, sizeof(roman_buffer)) == 0) {
            printf("%d -> %s\n", current_num, roman_buffer);
        } else {
            printf("%d -> Error: Invalid input or buffer size\n", current_num);
        }
    }

    return 0;
}