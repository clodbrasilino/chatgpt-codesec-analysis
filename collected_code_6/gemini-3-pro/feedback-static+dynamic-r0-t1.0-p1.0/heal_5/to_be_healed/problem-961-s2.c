#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

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
    char *s = NULL;
    size_t len = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ssize_t read;
    
    /* Possible weaknesses found:
     *  Although the value stored to 'read' is used in the enclosing expression, the value is never actually read from 'read' [deadcode.DeadStores]
     */
    while ((read = getline(&s, &len, stdin)) != -1) {
        s[strcspn(s, "\r\n")] = '\0';
        
        if (s[0] == '\0') {
            continue;
        }
        
        printf("%d\n", romanToInt(s));
    }
    
    free(s);
    return 0;
}