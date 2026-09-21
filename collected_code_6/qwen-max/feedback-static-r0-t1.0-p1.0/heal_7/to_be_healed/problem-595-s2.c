#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int countSwaps(const char *a, const char *b, size_t len) {
    int mismatch = 0;
    for (size_t i = 0; i < len; ++i) {
        if (a[i] != b[i]) {
            mismatch++;
        }
    }
    /* Possible weaknesses found:
     * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    return mismatch / 2 + (mismatch % 2);
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'str1="1100"', assigned value is "1100"
     */
    const char *str1 = "1100";
    const char *str2 = "1001";
    /* Possible weaknesses found:
     *  Assignment 'len1=strlen(str1)', assigned value is 4
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(str2);

    /* Possible weaknesses found:
     *  Condition 'len1!=len2' is always false
     *  Condition 'len1!=len2' is always false [knownConditionTrueFalse]
     */
    if (len1 != len2) {
        printf("Error: The two strings must be of the same length.\n");
        return 1;
    }

    int swaps = countSwaps(str1, str2, len1);
    printf("Minimum number of swaps required: %d\n", swaps);
    return 0;
}