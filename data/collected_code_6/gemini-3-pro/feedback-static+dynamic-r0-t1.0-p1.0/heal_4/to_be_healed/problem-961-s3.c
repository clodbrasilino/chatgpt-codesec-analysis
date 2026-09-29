#include <stdio.h>
#include <string.h>

int romanCharToInt(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

int romanToInt(const char *s) {
    if (s == NULL) {
        return 0;
    }

    int total = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        int currentValue = romanCharToInt(s[i]);
        
        if (currentValue == 0) {
            return -1;
        }

        int nextValue = romanCharToInt(s[i + 1]);

        if (currentValue < nextValue) {
            total -= currentValue;
        } else {
            total += currentValue;
        }
    }

    return total;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char roman[1024];

    while (fgets(roman, sizeof(roman), stdin) != NULL) {
        roman[strcspn(roman, " \t\r\n")] = '\0';
        
        if (roman[0] != '\0') {
            printf("%d\n", romanToInt(roman));
        }
    }

    return 0;
}