#define _POSIX_C_SOURCE 200809L
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
    char *buffer = NULL;
    size_t bufcap = 0;

    while (getline(&buffer, &bufcap, stdin) != -1) {
        char *token = strtok(buffer, " \t\n\r");
        while (token != NULL) {
            printf("%d\n", romanToInt(token));
            token = strtok(NULL, " \t\n\r");
        }
    }
    
    free(buffer);
    return 0;
}