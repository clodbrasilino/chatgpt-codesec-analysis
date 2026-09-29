#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4000, got 0
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
    int repeat_count = 0;
    char prev_char = '\0';
    const char *ptr = s;

    while (*ptr != '\0') {
        char c = toupper((unsigned char)*ptr);
        int curr_value = values[(unsigned char)c];

        if (curr_value == 0) {
            return 0;
        }

        if (c == prev_char) {
            repeat_count++;
            if (repeat_count > 3) {
                return 0;
            }
            if ((c == 'V' || c == 'L' || c == 'D') && repeat_count > 1) {
                return 0;
            }
        } else {
            repeat_count = 1;
        }

        if (prev_value > 0 && curr_value > prev_value) {
            if (!(prev_value == 1 || prev_value == 10 || prev_value == 100)) {
                return 0;
            }
            if (curr_value / prev_value > 10 || curr_value % prev_value != 0) {
                return 0;
            }
            if (prev_char == 'V' || prev_char == 'L' || prev_char == 'D') {
                return 0;
            }
            if (prev_value == 1 && !(curr_value == 5 || curr_value == 10)) {
                return 0;
            }
            if (prev_value == 10 && !(curr_value == 50 || curr_value == 100)) {
                return 0;
            }
            if (prev_value == 100 && !(curr_value == 500 || curr_value == 1000)) {
                return 0;
            }
            if (repeat_count > 1) {
                return 0;
            }
            total += curr_value - 2 * prev_value;
        } else {
            total += curr_value;
        }

        prev_value = curr_value;
        prev_char = c;
        ptr++;
    }

    return total;
}

int main(void) {
    const char *test_cases[] = {
        "III", "IV", "IX", "LVIII", "MCMXCIV",
        "XLII", "CDXLIV", "MMXXIV", "MMMDCCCLXXXVIII", "I",
        "C", "M", "XC", "CD", "MMMCMXCIX"
    };
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        int result = roman_to_int(test_cases[i]);
        printf("%s = %d\n", test_cases[i], result);
    }

    const char *invalid_tests[] = {
        "IIII", "VV", "IL", "IC", "XM", "", NULL, "ABC", "IVI", "CMC"
    };
    size_t num_invalid = sizeof(invalid_tests) / sizeof(invalid_tests[0]);

    for (size_t i = 0; i < num_invalid; i++) {
        int result = roman_to_int(invalid_tests[i]);
        printf("Invalid test %zu: %d\n", i + 1, result);
    }

    return 0;
}