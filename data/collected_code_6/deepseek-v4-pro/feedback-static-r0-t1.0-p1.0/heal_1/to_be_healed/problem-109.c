#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_odd_rotations(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(s);
    int *doubled = (int *)malloc(2 * n * sizeof(int));
    if (doubled == NULL) {
        return -1;
    }

    for (int i = 0; i < 2 * n; i++) {
        doubled[i] = s[i % n] - '0';
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        int value = 0;
        for (int j = 0; j < n; j++) {
            value = (value << 1) | doubled[i + j];
        }
        if (value % 2 == 1) {
            count++;
        }
    }

    free(doubled);
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%255s", input) != 1) {
        return 1;
    }

    int result = count_odd_rotations(input);
    if (result < 0) {
        return 1;
    }

    printf("%d\n", result);
    return 0;
}