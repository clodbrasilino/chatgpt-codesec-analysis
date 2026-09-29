#include <stdio.h>
#include <string.h>
#include <limits.h>

int minSwaps(char *str, size_t len) {
    int open = 0, close = 0, maxDiff = INT_MIN, swaps = 0;

    for (size_t i = 0; i < len; ++i) {
        if (str[i] == '(')
            ++open;
        else
            ++close;

        int currDiff = open - close;

        if (currDiff > maxDiff)
            maxDiff = currDiff;

        if (currDiff < 0) {
            swaps += -currDiff;
            open = 0;
            close = 0;
        }
    }

    return (maxDiff + swaps) / 2;
}

int main() {
    char str[] = "(()))(()";
    size_t len = strlen(str);
    printf("Minimum number of swaps: %d\n", minSwaps(str, len));
    return 0;
}