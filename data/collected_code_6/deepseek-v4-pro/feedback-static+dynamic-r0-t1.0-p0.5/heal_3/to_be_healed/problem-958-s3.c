#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void int_to_roman(int num, char *result, size_t result_size) {
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    if (result_size > 0) {
        result[0] = '\0';
    }
    size_t current_len = 0;
    
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t sym_len = strlen(symbols[i]);
            if (current_len + sym_len + 1 <= result_size) {
                /* Possible weaknesses found:
                 * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
                 */
                strncat(result + current_len, symbols[i], result_size - current_len - 1);
                current_len += sym_len;
                result[current_len] = '\0';
            }
            num -= values[i];
        }
    }
}

int main(void) {
    int numbers[] = {1, 4, 9, 58, 1994, 2023, 3999};
    int count = sizeof(numbers) / sizeof(numbers[0]);
    
    for (int i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char roman[32] = {0};
        int_to_roman(numbers[i], roman, sizeof(roman));
        printf("%d = %s\n", numbers[i], roman);
    }
    
    return 0;
}