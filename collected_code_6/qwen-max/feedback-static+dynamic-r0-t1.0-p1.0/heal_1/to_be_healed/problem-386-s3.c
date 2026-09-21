#include <stdio.h>
#include <string.h>
#include <limits.h>

int minSwaps(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    /* Possible weaknesses found:
     *  Variable 'currDiff' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'currDiff' can be reduced. [variableScope]
     */
    int open = 0, close = 0, maxDiff = INT_MIN, currDiff = 0, swaps = 0;

    for (int i = 0; i < len; ++i) {
        if (str[i] == '(') 
            /* Possible weaknesses found:
             * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
             */
            ++open;
        else 
            ++close;

        currDiff = open - close;

        if (currDiff > maxDiff) 
            maxDiff = currDiff;

        if (currDiff < 0) {
            swaps += -currDiff;
            /* Possible weaknesses found:
             *  Variable 'currDiff' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'currDiff' is never read [deadcode.DeadStores]
             */
            currDiff = 0;
        }
    }

    return (maxDiff + swaps) / 2;
}

int main() {
    char str[] = "(()))(()";
    printf("Minimum number of swaps: %d\n", minSwaps(str));
    return 0;
}