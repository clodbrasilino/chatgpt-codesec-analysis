#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  *  test case 2 failed: expected 'Not Possible', got -1
  */

int minSwaps(const char *str1, const char *str2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (len != strlen(str2)) {
        return -1;
    }

    int count1 = 0, count2 = 0;
    for (int i = 0; i < len; i++) {
        if (str1[i] == '1') count1++;
        if (str2[i] == '1') count2++;
    }

    if (count1 != count2) {
        return -1;
    }

    int swaps = 0;
    for (int i = 0; i < len; i++) {
        if (str1[i] != str2[i]) {
            swaps++;
        }
    }

    return swaps / 2;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[100], str2[100];

    printf("Enter first binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    scanf("%99s", str1);

    printf("Enter second binary string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    scanf("%99s", str2);

    int result = minSwaps(str1, str2);

    if (result == -1) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    return 0;
}