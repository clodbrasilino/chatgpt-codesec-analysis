#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'a' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'b' can be declared as pointer to const [constParameterPointer]
 */
int minSwapsToEqual(char *a, char *b, int len) {
    /* Possible weaknesses found:
     * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    int mismatch[2] = {0};
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            /* Possible weaknesses found:
             * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
             */
            mismatch[a[i] - '0']++;
        }
    }
    /* Possible weaknesses found:
     * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    if (mismatch[0] != mismatch[1]) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    return (mismatch[0] + 1) / 2;
}

int main() {
    char *a = "1100";
    char *b = "1001";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(a);
    int result = minSwapsToEqual(a, b, len);
    printf("%d\n", result);
    return 0;
}