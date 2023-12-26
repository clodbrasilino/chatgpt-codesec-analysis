#include <stdio.h>
#include <string.h>

int minSwaps(char* str1, char* str2) {
    /* Possible weaknesses found:
     *  Cannot determine that 'str1[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int n = strlen(str1);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str2[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int m = strlen(str2);

    if (n != m) {
        return -1;
    }

    int count0 = 0, count1 = 0, mismatch = 0;

    for (int i = 0; i < n; i++) {
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
    char str1[] = "0110";
    char str2[] = "1001";

    int swaps = minSwaps(str1, str2);

    printf("Minimum number of swaps required: %d\n", swaps);

    return 0;
}