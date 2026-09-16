#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_swaps(const char *s) {
    if (s == NULL) {
        return -1;
    }
    int balance = 0;
    int swaps = 0;
    size_t len = strlen(s);
    if (len % 2 != 0) {
        return -1;
    }
    for (size_t i = 0; i < len; i++) {
        if (s[i] == '[') {
            balance++;
        } else if (s[i] == ']') {
            balance--;
        } else {
            return -1;
        }
        if (balance < 0) {
            swaps++;
            balance = 1;
        }
    }
    if (balance != 0) {
        return -1;
    }
    return swaps;
}

int main(void) {
    const char *s = "]]][[[";
    int result = min_swaps(s);
    if (result == -1) {
        printf("Invalid input or cannot be balanced\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }
    return 0;
}