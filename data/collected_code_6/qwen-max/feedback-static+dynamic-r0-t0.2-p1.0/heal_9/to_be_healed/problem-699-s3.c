#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got <no output>
  *  test case 2 failed: expected 3, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  */

int minSwaps(const char *s1, const char *s2) {
    size_t len1 = 0;
    while (s1[len1] != '\0' && (s1[len1] == '0' || s1[len1] == '1')) len1++;
    if (s1[len1] != '\0') return -1;

    size_t len2 = 0;
    while (s2[len2] != '\0' && (s2[len2] == '0' || s2[len2] == '1')) len2++;
    if (s2[len2] != '\0') return -1;

    if (len1 != len2) return -1;

    int count[2] = {0, 0};
    for (size_t i = 0; i < len1; ++i) {
        if (s1[i] != s2[i]) {
            count[s1[i] - '0']++;
            count[s2[i] - '0']--;
        }
    }

    if (count[0] == 0 && count[1] == 0) {
        int mismatch = 0;
        for (size_t i = 0; i < len1; ++i) {
            if (s1[i] != s2[i]) {
                mismatch++;
            }
        }
        /* Possible weaknesses found:
         * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
         */
        return mismatch / 2;
    } else {
        return -1;
    }
}

int main() {
    const char s1[] = "1100";
    const char s2[] = "1001";
    int result = minSwaps(s1, s2);
    if (result >= 0) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Conversion not possible\n");
    }

    const char test1_s1[] = "110";
    const char test1_s2[] = "001";
    result = minSwaps(test1_s1, test1_s2);
    if (result >= 0) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Conversion not possible\n");
    }

    const char test2_s1[] = "1100";
    const char test2_s2[] = "0011";
    result = minSwaps(test2_s1, test2_s2);
    if (result >= 0) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Conversion not possible\n");
    }

    const char test3_s1[] = "101";
    const char test3_s2[] = "100";
    result = minSwaps(test3_s1, test3_s2);
    if (result >= 0) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Conversion not possible\n");
    }

    return 0;
}