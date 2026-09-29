#include <stdio.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *str1, const char *str2) {
    size_t i = 0;
    int mismatch_1_to_0 = 0;
    int mismatch_0_to_1 = 0;

    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    while (str1[i] != '\0' && str2[i] != '\0') {
        if ((str1[i] != '0' && str1[i] != '1') || (str2[i] != '0' && str2[i] != '1')) {
            return -1;
        }

        if (str1[i] != str2[i]) {
            if (str1[i] == '1') {
                mismatch_1_to_0++;
            } else {
                mismatch_0_to_1++;
            }
        }
        i++;
    }

    if (str1[i] != '\0' || str2[i] != '\0') {
        return -1;
    }

    if (mismatch_1_to_0 != mismatch_0_to_1) {
        return -1;
    }

    return mismatch_1_to_0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[100000];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[100000];

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%99999s %99999s", str1, str2) == 2) {
        int result = min_swaps(str1, str2);

        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Not Possible\n");
        }
    }

    return 0;
}