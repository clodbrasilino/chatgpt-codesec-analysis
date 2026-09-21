#include <stdio.h>
#include <stdlib.h>

int minSwaps(const char *str) {
    int len = 0;
    while (str[len] != '\0') len++;
    int open = 0, close = 0, swaps = 0, imbalance = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == '[') open++;
        else if (str[i] == ']') close++;

        /* Possible weaknesses found:
         * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
         */
        if (close > open) {
            imbalance++;
            swaps += imbalance;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    if (open != close) return -1;

    return swaps;
}

int main() {
    const char str[] = "[]][][";
    int result = minSwaps(str);
    if (result == -1)
        printf("The input string is not balanced.\n");
    else
        printf("Minimum number of swaps required: %d\n", result);

    return 0;
}