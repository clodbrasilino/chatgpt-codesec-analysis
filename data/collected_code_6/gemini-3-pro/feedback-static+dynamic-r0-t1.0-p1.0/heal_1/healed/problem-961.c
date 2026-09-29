#include <stdio.h>
#include <stdlib.h>

int romanCharToInt(char c) {
    switch (c) {
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
    if (s == NULL) {
        return -1;
    }

    int total = 0;
    int i = 0;

    while (s[i] != '\0') {
        int currentVal = romanCharToInt(s[i]);
        if (currentVal == -1) {
            return -1;
        }

        if (s[i + 1] != '\0') {
            int nextVal = romanCharToInt(s[i + 1]);
            if (nextVal == -1) {
                return -1;
            }

            if (currentVal < nextVal) {
                total -= currentVal;
            } else {
                total += currentVal;
            }
        } else {
            total += currentVal;
        }
        i++;
    }

    return total;
}

int main(void) {
    const char *roman1 = "III";
    const char *roman2 = "IV";
    const char *roman3 = "IX";
    const char *roman4 = "LVIII";
    const char *roman5 = "MCMXCIV";
    const char *invalid = "ABC";

    printf("%d\n", romanToInt(roman1));
    printf("%d\n", romanToInt(roman2));
    printf("%d\n", romanToInt(roman3));
    printf("%d\n", romanToInt(roman4));
    printf("%d\n", romanToInt(roman5));
    printf("%d\n", romanToInt(invalid));
    printf("%d\n", romanToInt(NULL));

    return 0;
}