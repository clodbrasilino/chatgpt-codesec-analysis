#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *s1, const char *s2) {
    int count1 = 0, count2 = 0;
    int mismatched_ones = 0, mismatched_zeros = 0;
    int swaps = 0;
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] == '1') count1++;
        if (s2[i] == '1') count2++;
        i++;
    }

    if (s1[i] != s2[i]) return -1;

    if (count1 != count2) return -1;

    i = 0;
    while (s1[i] != '\0') {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') mismatched_ones++;
            else mismatched_zeros++;
        }
        i++;
    }

    swaps = (mismatched_ones > mismatched_zeros) ? mismatched_ones : mismatched_zeros;
    return swaps;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[102] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[102] = {0};

    printf("Enter first binary string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }
    str1[strcspn(str1, "\n")] = '\0';

    printf("Enter second binary string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }
    str2[strcspn(str2, "\n")] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(str2);
    if (len1 != len2) {
        printf("Strings must be of equal length\n");
        return 1;
    }

    int result = min_swaps(str1, str2);
    if (result == -1) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    return 0;
}