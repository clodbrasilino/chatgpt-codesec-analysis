#include <stdio.h>
#include <stdlib.h>

int find_min_rotations(const char *str) {
    if (str == NULL) {
        return -1;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    if (len == 0) {
        return 0;
    }

    char *temp = (char *)malloc(2 * len + 1);
    if (temp == NULL) {
        return -1;
    }

    for (size_t i = 0; i < len; i++) {
        temp[i] = str[i];
        temp[i + len] = str[i];
    }
    temp[2 * len] = '\0';

    int min_rotations = (int)len;
    for (size_t i = 1; i <= len; i++) {
        int match = 1;
        for (size_t j = 0; j < len; j++) {
            if (str[j] != temp[i + j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            min_rotations = (int)i;
            break;
        }
    }

    free(temp);
    return min_rotations;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[4096];
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%4095s", str) == 1) {
        int rotations = find_min_rotations(str);
        if (rotations != -1) {
            printf("%d\n", rotations);
        }
    }
    return 0;
}