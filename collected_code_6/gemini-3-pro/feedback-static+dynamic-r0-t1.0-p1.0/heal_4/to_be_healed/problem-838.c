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
        if (s1[i] != '0' && s1[i] != '1') return -1;
        if (s2[i] != '0' && s2[i] != '1') return -1;

        if (s1[i] == '0' && s2[i] == '1') {
            mismatches_01++;
        } else if (s1[i] == '1' && s2[i] == '0') {
            mismatches_10++;
        }
        
        i++;
    }

    if (s1[i] != '\0' || s2[i] != '\0' || i == 0) {
        return -1;
    }

    if ((mismatches_01 + mismatches_10) % 2 != 0) {
        return -1;
    }

    return (mismatches_01 / 2) + (mismatches_10 / 2) + (mismatches_01 % 2) * 2;
}

int main(void) {
    size_t max_len = 1000005;
    char *s1 = (char *)calloc(max_len, sizeof(char));
    char *s2 = (char *)calloc(max_len, sizeof(char));

    if (s1 == NULL || s2 == NULL) {
        free(s1);
        free(s2);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%1000000s", s1) == 1 && scanf("%1000000s", s2) == 1) {
        int result = min_swaps(s1, s2);
        printf("%d\n", result);
    }

    free(s1);
    free(s2);

    return 0;
}