#include <stdio.h>
#include <string.h>

int countSwaps(const char *a, const char *b, size_t len) {
    int mismatch = 0;
    for (size_t i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            mismatch++;
        }
    }
    /* Possible weaknesses found:
     * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    return mismatch / 2 + (mismatch & 1);
}

int main() {
    char str1[] = "1100";
    char str2[] = "1001";
    /* Possible weaknesses found:
     *  Assignment 'len1=sizeof(str1)-1', assigned value is 4
     */
    size_t len1 = sizeof(str1) - 1;
    size_t len2 = sizeof(str2) - 1;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (str1[len1-1] != '\0' || str2[len2-1] != '\0') {
        printf("Error: The strings must be null-terminated.\n");
        return 1;
    }

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