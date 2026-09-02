#include <stdio.h>
#include <string.h>
#include <limits.h>

int minSwaps(char *str) {
    int len = strlen(str);
    /* Possible weaknesses found:
     *  Variable 'currDiff' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'currDiff' can be reduced. [variableScope]
     */
    int open = 0, close = 0, maxDiff = INT_MIN, currDiff = 0, swaps = 0;

    for (int i = 0; i < len; ++i) {
        if (str[i] == '(') 
            ++open;
        else 
            ++close;

        currDiff = open - close;

        if (currDiff > maxDiff) 
            maxDiff = currDiff;

        if (currDiff < 0) {
            swaps += -currDiff;
            /* Possible weaknesses found:
             *  Value stored to 'currDiff' is never read [deadcode.DeadStores]
             *  Variable 'currDiff' is assigned a value that is never used. [unreadVariable]
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