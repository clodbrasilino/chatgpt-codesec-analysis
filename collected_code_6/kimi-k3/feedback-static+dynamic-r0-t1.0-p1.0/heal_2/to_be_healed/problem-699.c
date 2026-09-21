#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_swaps(const char *s1, const char *s2, size_t len1, size_t len2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    if (len1 != len2) {
        return -1;
    }

    int diff = 0;
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            diff++;
        }
    }

    if (diff % 2 != 0) {
        return -1;
    }

    return diff / 2;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s1[100];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s2[100];
    size_t len1, len2;

    if (fgets(s1, sizeof(s1), stdin) == NULL) {
        return 1;
    }
    if (fgets(s2, sizeof(s2), stdin) == NULL) {
        return 1;
    }

    len1 = strcspn(s1, "\n");
    s1[len1] = '\0';
    len2 = strcspn(s2, "\n");
    s2[len2] = '\0';

    int result = min_swaps(s1, s2, len1, len2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    return 0;
}