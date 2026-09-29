#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_swaps(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    int mismatches_01 = 0;
    int mismatches_10 = 0;
    size_t i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }

        if (s1[i] == '0' && s2[i] == '1') {
            mismatches_01++;
        } else if (s1[i] == '1' && s2[i] == '0') {
            mismatches_10++;
        }
        i++;
    }

    if (s1[i] != '\0' || s2[i] != '\0') {
        return -1;
    }

    if ((mismatches_01 + mismatches_10) % 2 != 0) {
        return -1;
    }

    int swaps = (mismatches_01 / 2) + (mismatches_10 / 2);
    
    if (mismatches_01 % 2 != 0) {
        swaps += 2;
    }

    return swaps;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s1[100001];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s2[100001];

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%100000s %100000s", s1, s2) == 2) {
        int result = min_swaps(s1, s2);
        printf("%d\n", result);
    }

    return 0;
}