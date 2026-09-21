#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 's' can be declared as pointer to const [constParameterPointer]
 */
int min_swaps(char *s, size_t size) {
    int open = 0, close = 0, maxDiff = 0;

    for (size_t i = 0; i < size; i++) {
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
    /* Possible weaknesses found:
     *  %zu in format string (no. 1) requires 'size_t' but the argument type is 'signed int'. [invalidPrintfArgType_uint]
     */
    printf("Minimum swaps required: %zu\n", min_swaps(s, sizeof(s) - 1));
    return 0;
}