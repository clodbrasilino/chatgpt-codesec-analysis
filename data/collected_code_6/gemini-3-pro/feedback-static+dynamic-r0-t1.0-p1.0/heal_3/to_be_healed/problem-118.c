#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) {
    int ch;
    int in_word = 0;
    int first = 1;

    printf("[");
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF) {
        if (isspace(ch)) {
            if (in_word) {
                printf("'");
                in_word = 0;
            }
        } else {
            if (!in_word) {
                if (!first) {
                    printf(", ");
                }
                printf("'");
                first = 0;
                in_word = 1;
            }
            putchar(ch);
        }
    }
    if (in_word) {
        printf("'");
    }
    printf("]\n");
    
    return 0;
}