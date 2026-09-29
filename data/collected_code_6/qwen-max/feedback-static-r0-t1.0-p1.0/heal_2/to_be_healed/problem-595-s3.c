#include <stdio.h>
#include <string.h>

int minSwaps(const char* s1, const char* s2) {
    int count[2] = {0, 0};
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(s1);

    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            count[s1[i] - '0']++;
        }
    }

    return count[0] == count[1] ? count[0] : -1;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 's1' can be declared as const array [constVariable]
     */
    char s1[] = "1100";
    /* Possible weaknesses found:
     *  Variable 's2' can be declared as const array [constVariable]
     */
    char s2[] = "0011";

    int swaps = minSwaps(s1, s2);
    if (swaps != -1) {
        printf("Minimum number of swaps: %d\n", swaps);
    } else {
        printf("Cannot convert string s1 to s2 with swaps.\n");
    }

    return 0;
}