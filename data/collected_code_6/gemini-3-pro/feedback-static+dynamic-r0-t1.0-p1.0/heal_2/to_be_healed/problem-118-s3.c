#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[256];
    int first = 1;

    printf("[");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    while (scanf("%255s", word) == 1) {
        if (!first) {
            printf(", ");
        }
        printf("'%s'", word);
        first = 0;
    }
    printf("]\n");

    return 0;
}