#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 's' can be declared as pointer to const [constParameterPointer]
 */
int min_swaps(char *s, size_t len) {
    int open = 0, close = 0, maxDiff = 0;

    for (size_t i = 0; i < len; i++) {
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
    size_t len = sizeof(s) / sizeof(s[0]) - 1;
    printf("Minimum swaps required: %d\n", min_swaps(s, len));
    return 0;
}