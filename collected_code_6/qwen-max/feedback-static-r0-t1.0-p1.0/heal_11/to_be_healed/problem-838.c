#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

size_t safe_strlen(const char *s) {
    const char *p = s;
    while (*p != '\0') p++;
    return p - s;
}

int minSwaps(const char *s1, const char *s2) {
    size_t len1 = safe_strlen(s1);
    size_t len2 = safe_strlen(s2);
    if (len1 != len2 || s1[len1 - 1] != '\0' || s2[len2 - 1] != '\0') return -1;

    /* Possible weaknesses found:
     * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    int mismatch[2] = {0, 0};
    for (size_t i = 0; i < len1; ++i) {
        if (s1[i] != s2[i] && (s1[i] == '0' || s1[i] == '1')) {
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
    const char s1[] = "1100";
    const char s2[] = "1001";
    printf("Minimum swaps: %d\n", minSwaps(s1, s2));
    return 0;
}