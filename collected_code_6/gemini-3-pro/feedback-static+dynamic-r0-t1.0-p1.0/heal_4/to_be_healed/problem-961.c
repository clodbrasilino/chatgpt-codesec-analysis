#include <stdio.h>
#include <stdlib.h>
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
        default: return -1;
    }
}

int romanToInt(const char *s) {
    if (s == NULL) {
        return -1;
    }

    int total = 0;
    int i = 0;

    while (s[i] != '\0' && s[i] != '\n' && s[i] != '\r' && s[i] != ' ') {
        int currentVal = romanCharToInt(s[i]);
        if (currentVal == -1) {
            return -1;
        }

        if (s[i + 1] != '\0' && s[i + 1] != '\n' && s[i + 1] != '\r' && s[i + 1] != ' ') {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[2048];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *token = strtok(buffer, " \t\n\r");
        while (token != NULL) {
            printf("%d\n", romanToInt(token));
            token = strtok(NULL, " \t\n\r");
        }
    }
    
    return 0;
}