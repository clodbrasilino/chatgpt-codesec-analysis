#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 2 failed: expected 'Not Possible', got <no output>
  *  test case 1 failed: expected 'Not Possible', got <no output>
  */

int min_swaps(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t len1 = 0;
    while (str1[len1] != '\0') {
        len1++;
    }
    
    size_t len2 = 0;
    while (str2[len2] != '\0') {
        len2++;
    }

    if (len1 != len2) {
        return -1;
    }

    int count_0_1 = 0;
    int count_1_0 = 0;

    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != '0' && str1[i] != '1') {
            return -1;
        }
        if (str2[i] != '0' && str2[i] != '1') {
            return -1;
        }

        if (str1[i] == '0' && str2[i] == '1') {
            count_0_1++;
        } else if (str1[i] == '1' && str2[i] == '0') {
            count_1_0++;
        }
    }

    if (count_0_1 == count_1_0) {
        return count_0_1;
    }

    return -1;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[1024];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[1024];

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%1023s %1023s", str1, str2) == 2) {
        int result = min_swaps(str1, str2);

        if (result == -1) {
            printf("Not Possible\n");
        } else {
            printf("%d\n", result);
        }
    }

    return 0;
}