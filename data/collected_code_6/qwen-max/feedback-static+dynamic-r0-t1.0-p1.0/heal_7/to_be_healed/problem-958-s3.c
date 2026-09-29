#include <stdio.h>
#include <string.h>

const char *const romanNumerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'IV', got <no output>
  *  test case 1 failed: expected 'L', got <no output>
  *  test case 0 failed: expected 'I', got <no output>
  */

char *intToRoman(int num) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    static char roman[20];
    memset(roman, 0, sizeof(roman));

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(roman);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (len + strlen(romanNumerals[i]) < sizeof(roman) - 1) {
                /* Possible weaknesses found:
                 * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
                 */
                strncat(roman, romanNumerals[i], sizeof(roman) - len - 1);
                num -= values[i];
            } else {
                break;
            }
        }
    }

    return roman;
}

int main() {
    int number = 1994;
    printf("%s\n", intToRoman(number));
    return 0;
}