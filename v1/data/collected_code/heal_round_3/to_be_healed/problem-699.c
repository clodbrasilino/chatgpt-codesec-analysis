#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool strIsValid(const char* str) {
    if (str == NULL) {
        return false;
    }
    while (*str) {
        if (*str != '0' && *str != '1') {
            return false;
        }
        str++;
    }
    return true;
}

int minSwaps(const char* str1, const char* str2) {

    if (!strIsValid(str1) || !strIsValid(str2)) {
        return -1;
    }
    
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t n = strlen(str1);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t m = strlen(str2);

    if (n != m) {
        return -1;
    }

    int count0 = 0, count1 = 0, mismatch = 0;

    for (size_t i = 0; i < n; i++) {
        if (str1[i] != str2[i]) {
            mismatch++;
            if (str1[i] == '0') {
                count0++;
            } else {
                count1++;
            }
        }
    }

    /* Possible weaknesses found:
     *   Function does not check the second iterator for over-read conditions  (CWE-126). This function is often discouraged by most C++ coding standards  in favor of its safer alternatives provided since C++14. Consider using a  form of this function that checks the second iterator before potentially  overflowing it.
     */
    if (mismatch % 2 != 0) {
        return -1;
    }

    /* Possible weaknesses found:
     *   Function does not check the second iterator for over-read conditions  (CWE-126). This function is often discouraged by most C++ coding standards  in favor of its safer alternatives provided since C++14. Consider using a  form of this function that checks the second iterator before potentially  overflowing it.
     */
    return mismatch / 2 + (count0 % 2 == 0 ? count0 / 2 : count0 / 2 + 1);
}

int main() {
    const char* str1 = "0110";
    const char* str2 = "1001";

    int swaps = minSwaps(str1, str2);

    printf("Minimum number of swaps required: %d\n", swaps);

    return 0;
}