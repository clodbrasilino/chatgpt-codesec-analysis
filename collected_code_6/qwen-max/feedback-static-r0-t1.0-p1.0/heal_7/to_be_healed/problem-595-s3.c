#include <stdio.h>
#include <string.h>

int minSwaps(const char* s1, const char* s2) {
    if (!s1 || !s2) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n2 = strlen(s2);
    if (n1 != n2) {
        return -1;
    }

    int count[2] = {0, 0};
    for (size_t i = 0; i < n1; i++) {
        if (s1[i] != s2[i]) {
            count[s1[i] - '0']++;
        }
    }

    return count[0] == count[1] ? count[0] : -1;
}

int main() {
    const char s1[] = "1100";
    const char s2[] = "0011";

    int swaps = minSwaps(s1, s2);
    if (swaps != -1) {
        printf("Minimum number of swaps: %d\n", swaps);
    } else {
        printf("Cannot convert string s1 to s2 with swaps.\n");
    }

    return 0;
}