#include <stdio.h>
#include <string.h>

int countSwaps(const char *a, const char *b, int len) {
    int mismatch = 0, count[2] = {0, 0};
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            mismatch++;
            count[a[i] - '0']++;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    return mismatch / 2 + (mismatch & 1 ? 1 : 0);
}

int main() {
    char str1[] = "1100";
    char str2[] = "1001";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str1);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (len != strlen(str2)) {
        printf("Error: The two strings must be of the same length.\n");
        return 1;
    }

    int swaps = countSwaps(str1, str2, len);
    printf("Minimum number of swaps required: %d\n", swaps);
    return 0;
}