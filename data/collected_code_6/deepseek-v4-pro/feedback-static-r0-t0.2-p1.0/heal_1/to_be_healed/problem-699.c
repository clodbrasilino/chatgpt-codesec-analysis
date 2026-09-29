#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_swaps_to_convert(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(s2);

    if (len1 != len2) {
        return -1;
    }

    int count1 = 0, count2 = 0;
    int mismatch_positions = 0;
    int ones_in_mismatch = 0;

    for (size_t i = 0; i < len1; i++) {
        if (s1[i] != '0' && s1[i] != '1') {
            return -1;
        }
        if (s2[i] != '0' && s2[i] != '1') {
            return -1;
        }

        if (s1[i] == '1') count1++;
        if (s2[i] == '1') count2++;

        if (s1[i] != s2[i]) {
            mismatch_positions++;
            if (s1[i] == '1') {
                ones_in_mismatch++;
            }
        }
    }

    if (count1 != count2) {
        return -1;
    }

    return ones_in_mismatch;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[1000];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[1000];

    printf("Enter first binary string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    str1[strcspn(str1, "\n")] = '\0';

    printf("Enter second binary string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    str2[strcspn(str2, "\n")] = '\0';

    int result = min_swaps_to_convert(str1, str2);

    if (result == -1) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    return 0;
}