#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 'Not Possible', got <no output>
  *  test case 2 failed: expected 3, got <no output>
  */

int minSwaps(const char *s1, const char *s2) {
    int count[2] = {0, 0};
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(s2) != len) return -1;
    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            count[s1[i] - '0']++;
        }
    }
    return (count[0] + count[1]) / 2;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 's1' can be declared as const array [constVariable]
     */
    char s1[] = "1100";
    /* Possible weaknesses found:
     *  Variable 's2' can be declared as const array [constVariable]
     */
    char s2[] = "1001";
    int result = minSwaps(s1, s2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }
    return 0;
}