#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 100, got <no output>
  *  test case 1 failed: expected 4000, got <no output>
  *  test case 0 failed: expected 3986, got <no output>
  */

int romanToInt(const char *s) {
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int i, num = 0;

    for (i = 0; i < 13; ++i) {
        while (strncmp(s, roman[i], strlen(roman[i])) == 0) {
            num += values[i];
            s += strlen(roman[i]);
        }
    }

    return num;
}

int main() {
    const char *inputs[] = {"MCMXCIV", "MMMCMXCIX", "CCCXCIX", "CMI"};
    /* Possible weaknesses found:
     *  Variable 'expected_outputs' can be declared as const array [constVariable]
     */
    int expected_outputs[] = {1994, 3999, 399, 901};
    int i;

    for (i = 0; i < 4; ++i) {
        int result = romanToInt(inputs[i]);
        if (result == expected_outputs[i]) {
            printf("Correct: %s -> %d\n", inputs[i], result);
        } else {
            printf("Incorrect: %s -> %d (Expected: %d)\n", inputs[i], result, expected_outputs[i]);
        }
    }

    return 0;
}