#include <stdio.h>
#include <string.h>

int romanCharToInt(char c) {
    switch(c) {
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
    int prevValue = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        int currentValue = romanCharToInt(s[i]);
        
        if (currentValue == -1) {
            return -1;
        }

        total += currentValue;

        if (prevValue != 0 && currentValue > prevValue) {
            total -= 2 * prevValue;
        }
        
        prevValue = currentValue;
    }

    return total;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s[2048];
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    while (scanf("%2047s", s) == 1) {
        printf("%d\n", romanToInt(s));
    }
    return 0;
}