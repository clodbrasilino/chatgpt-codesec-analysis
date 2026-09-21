#include <stdio.h>
#include <string.h>

int findMinRotations(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(str);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[2*n + 1];
    snprintf(temp, sizeof(temp), "%s%s", str, str);

    for (int i = 1; i <= n; i++) {
        if (strncmp(temp + i, str, n) == 0) {
            return i;
        }
    }
    return n;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'str' can be declared as const array [constVariable]
     */
    char str[] = "abcde";
    printf("Minimum rotations: %d\n", findMinRotations(str));
    return 0;
}