#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 1
  *  test case 0 failed: expected 1, got 2
  */

/* Possible weaknesses found:
 *  Parameter 's2' can be declared as pointer to const [constParameterPointer]
 */
int minSwaps(char *s1, char *s2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    int mismatch[2] = {0, 0};
    for (int i = 0; i < len; ++i) {
        if (s1[i] != s2[i]) {
            /* Possible weaknesses found:
             * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
             */
            mismatch[s1[i] - '0']++;
        }
    }
    int swaps = 0;
    /* Possible weaknesses found:
     * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    while (mismatch[0] > 0 && mismatch[1] > 0) {
        swaps++;
        /* Possible weaknesses found:
         * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
         */
        mismatch[0]--;
        /* Possible weaknesses found:
         * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
         */
        mismatch[1]--;
    }
    /* Possible weaknesses found:
     * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    return swaps + (mismatch[0] / 2) * 2 + (mismatch[1] / 2) * 2;
}

int main() {
    char s1[] = "1100";
    char s2[] = "1001";
    printf("Minimum swaps: %d\n", minSwaps(s1, s2));
    return 0;
}