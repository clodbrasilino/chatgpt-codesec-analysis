#include <stdio.h>
#include <string.h>
#include <ctype.h>

int romanCharToInt(char c) {
    switch (toupper(c)) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return -1;
    }
}

int romanToInt(const char *s) {
    if (s == NULL || *s == '\0') {
        return -1;
    }

    int result = 0;
    size_t len = strlen(s);
    size_t i;

    for (i = 0; i < len; i++) {
        int current = romanCharToInt(s[i]);
        if (current == -1) {
            return -1;
        }

        if (i + 1 < len) {
            int next = romanCharToInt(s[i + 1]);
            if (next == -1) {
                return -1;
            }
            if (current < next) {
                result -= current;
            } else {
                result += current;
            }
        } else {
            result += current;
        }
    }

    return result;
}

int main(void) {
    const char *tests[] = {
        "III", "IV", "IX", "LVIII", "MCMXCIV", "MMXXIV", "XLII", "CDXLIV"
    };
    size_t numTests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < numTests; i++) {
        int value = romanToInt(tests[i]);
        if (value != -1) {
            printf("%s = %d\n", tests[i], value);
        } else {
            printf("%s = Invalid Roman numeral\n", tests[i]);
        }
    }

    return 0;
}