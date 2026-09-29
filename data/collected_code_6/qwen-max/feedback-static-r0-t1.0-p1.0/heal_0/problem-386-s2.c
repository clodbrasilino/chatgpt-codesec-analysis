#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_swaps(char *s) {
    int len = strlen(s);
    int open = 0, close = 0, maxDiff = 0;

    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            open++;
        } else {
            close++;
        }
        maxDiff = (maxDiff > (open - close)) ? maxDiff : (open - close);
    }

    return (maxDiff + 1) / 2;
}

int main() {
    char s[] = "(())))(";
    printf("Minimum swaps required: %d\n", min_swaps(s));
    return 0;
}