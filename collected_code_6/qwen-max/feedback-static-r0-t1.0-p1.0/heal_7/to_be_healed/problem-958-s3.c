#include <stdio.h>
#include <string.h>

char *intToRoman(int num) {
    const char *romanNumerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    static char roman[20];
    int index = 0;

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(romanNumerals[i]);
            if (index + len < sizeof(roman) - 1) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(roman + index, romanNumerals[i], len);
                roman[index + len] = '\0'; // Ensure null-termination
                index += len;
            } else {
                break;
            }
            num -= values[i];
        }
    }

    return roman;
}

int main() {
    int number = 1994;
    printf("%s\n", intToRoman(number));
    return 0;
}