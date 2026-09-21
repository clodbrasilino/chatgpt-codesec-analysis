#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 100, got <no output>
  *  test case 0 failed: expected 3986, got <no output>
  *  test case 1 failed: expected 4000, got <no output>
  */

int roman_to_int(const char *s) {
    int values[256] = {0};
    values['I'] = 1;
    values['V'] = 5;
    values['X'] = 10;
    values['L'] = 50;
    values['C'] = 100;
    values['D'] = 500;
    values['M'] = 1000;

    if (s == NULL || *s == '\0') {
        return 0;
    }

    int total = 0;
    int prev_value = 0;
    const char *ptr = s;

    while (*ptr != '\0') {
        char c = toupper((unsigned char)*ptr);
        int curr_value = values[(unsigned char)c];

        if (curr_value == 0) {
            return 0;
        }

        if (prev_value < curr_value) {
            total += curr_value - 2 * prev_value;
        } else {
            total += curr_value;
        }
        prev_value = curr_value;
        ptr++;
    }

    return total;
}

int main(void) {
    const char *test_cases[] = {
        "III", "IV", "IX", "LVIII", "MCMXCIV",
        "XLII", "CDXLIV", "MMXXIV", "MMMDCCCLXXXVIII", "I"
    };
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        int result = roman_to_int(test_cases[i]);
        printf("%s = %d\n", test_cases[i], result);
    }

    const char *invalid_tests[] = {
        "IIII", "VV", "IL", "IC", "XM", "", NULL, "ABC"
    };
    size_t num_invalid = sizeof(invalid_tests) / sizeof(invalid_tests[0]);

    for (size_t i = 0; i < num_invalid; i++) {
        int result = roman_to_int(invalid_tests[i]);
        printf("Invalid test %zu: %d\n", i + 1, result);
    }

    return 0;
}