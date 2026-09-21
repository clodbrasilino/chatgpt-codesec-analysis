#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got 1
  */

/* Possible weaknesses found:
 *  Parameter 's2' can be declared as pointer to const [constParameterPointer]
 */
int minSwaps(char *s1, char *s2) {
    int count[2] = {0, 0};
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(s1);
    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            count[s1[i] - '0']++;
        }
    }
    return (count[0] + count[1]) / 2;
}

int main() {
    char s1[] = "1100";
    char s2[] = "1001";
    int result = minSwaps(s1, s2);
    printf("Minimum swaps required: %d\n", result);
    return 0;
}