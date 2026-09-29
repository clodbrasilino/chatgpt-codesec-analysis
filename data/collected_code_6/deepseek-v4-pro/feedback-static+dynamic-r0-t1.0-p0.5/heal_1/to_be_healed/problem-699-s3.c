#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 'Not Possible', got <no output>
  */

int min_swaps(const char *str1, const char *str2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str1);
    int count1 = 0, count2 = 0;
    int pos1 = -1, pos2 = -1;
    int swaps = 0;

    for (int i = 0; i < len; i++) {
        if (str1[i] != str2[i]) {
            if (str1[i] == '0') {
                count1++;
                if (pos1 == -1) pos1 = i;
            } else {
                count2++;
                if (pos2 == -1) pos2 = i;
            }
        }
    }

    if (count1 != count2) return -1;

    while (pos1 != -1 && pos2 != -1) {
        swaps++;
        pos1 = -1;
        pos2 = -1;
        for (int i = 0; i < len; i++) {
            if (str1[i] != str2[i]) {
                if (str1[i] == '0' && pos1 == -1) pos1 = i;
                if (str1[i] == '1' && pos2 == -1) pos2 = i;
            }
        }
    }

    return swaps;
}

int main(void) {
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(str1) != strlen(str2)) {
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