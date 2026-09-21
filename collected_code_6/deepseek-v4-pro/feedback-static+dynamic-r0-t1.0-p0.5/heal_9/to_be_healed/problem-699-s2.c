#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 2
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *s1, const char *s2) {
    int count1 = 0, count2 = 0;
    int mismatched_ones = 0, mismatched_zeros = 0;
    int swaps = 0;
    int i = 0;
    int len1 = 0, len2 = 0;

    if (s1 == NULL || s2 == NULL) return -1;

    len1 = (int)strnlen(s1, 101);
    len2 = (int)strnlen(s2, 101);

    if (len1 != len2) return -1;
    if (len1 == 0) return 0;

    for (i = 0; i < len1; i++) {
        if (s1[i] == '1') count1++;
        if (s2[i] == '1') count2++;
    }

    if (count1 != count2) return -1;

    mismatched_ones = 0;
    mismatched_zeros = 0;

    for (i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') mismatched_ones++;
            else mismatched_zeros++;
        }
    }

    if (mismatched_ones != mismatched_zeros) return -1;

    swaps = mismatched_ones / 2;
    if (mismatched_ones % 2 != 0) swaps++;

    return swaps;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[102];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[102];
    size_t len1, len2;
    size_t i;
    int result;

    printf("Enter first binary string: ");
    if (fgets(str1, (int)sizeof(str1), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }
    str1[strcspn(str1, "\n")] = '\0';

    printf("Enter second binary string: ");
    if (fgets(str2, (int)sizeof(str2), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }
    str2[strcspn(str2, "\n")] = '\0';

    len1 = strnlen(str1, sizeof(str1));
    len2 = strnlen(str2, sizeof(str2));

    if (len1 != len2) {
        printf("Strings must be of equal length\n");
        return 1;
    }

    if (len1 == 0 || len1 > 100) {
        printf("Invalid string length\n");
        return 1;
    }

    for (i = 0; i < len1; i++) {
        if ((str1[i] != '0' && str1[i] != '1') ||
            (str2[i] != '0' && str2[i] != '1')) {
            printf("Invalid binary string\n");
            return 1;
        }
    }

    result = min_swaps(str1, str2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    return 0;
}