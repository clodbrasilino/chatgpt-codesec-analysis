#include <stdio.h>
#include <string.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'str' can be declared as pointer to const [constParameterPointer]
 */
int minSwaps(char *str, size_t len) {
    int open = 0, close = 0, maxDiff = INT_MIN, swaps = 0;

    for (int i = 0; i < len; ++i) {
        if (str[i] == '(')
            /* Possible weaknesses found:
             * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
             */
            ++open;
        else
            ++close;

        int currDiff = open - close;

        if (currDiff > maxDiff)
            maxDiff = currDiff;

        if (currDiff < 0) {
            swaps += -currDiff;
            open = close;
        }
    }

    return (maxDiff + swaps) / 2;
}

int main() {
    char str[] = "(()))(()";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    printf("Minimum number of swaps: %d\n", minSwaps(str, len));
    return 0;
}