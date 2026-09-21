#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minSwapsToEqual(const char *a, const char *b, size_t len) {
    /* Possible weaknesses found:
     * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    int mismatch[2] = {0};
    for (size_t i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            if (a[i] == '0' || a[i] == '1') {
                /* Possible weaknesses found:
                 * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
                 */
                mismatch[a[i] - '0']++;
            }
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
    /* Possible weaknesses found:
     *  Assignment 'a="1100"', assigned value is "1100"
     */
    const char *a = "1100";
    const char *b = "1001";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Assignment 'len_a=strlen(a)', assigned value is 4
     */
    size_t len_a = strlen(a);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_b = strlen(b);

    /* Possible weaknesses found:
     *  Condition 'len_a!=len_b' is always false [knownConditionTrueFalse]
     *  Condition 'len_a!=len_b' is always false
     */
    if (len_a != len_b) {
        printf("Strings must be of equal length\n");
        return 1;
    }

    int result = minSwapsToEqual(a, b, len_a);
    printf("%d\n", result);

    return 0;
}