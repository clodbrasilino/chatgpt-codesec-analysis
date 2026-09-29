#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t len1 = strnlen(str1, 2048);
    size_t len2 = strnlen(str2, 2048);

    if (len1 != len2) {
        return -1;
    }

    int count_zero_to_one = 0;
    int count_one_to_zero = 0;

    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != '0' && str1[i] != '1') {
            return -1;
        }
        if (str2[i] != '0' && str2[i] != '1') {
            return -1;
        }

        if (str1[i] == '0' && str2[i] == '1') {
            count_zero_to_one++;
        } else if (str1[i] == '1' && str2[i] == '0') {
            count_one_to_zero++;
        }
    }

    if (count_zero_to_one != count_one_to_zero) {
        return -1;
    }

    return count_zero_to_one;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[2048] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[2048] = {0};

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%2047s", str1) == 1 && scanf("%2047s", str2) == 1) {
        int result = min_swaps(str1, str2);

        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Not Possible\n");
        }
    } else {
        printf("Not Possible\n");
    }

    return 0;
}