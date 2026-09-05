#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minSwapsToBalance(const char *s) {
    if (s == NULL) {
        return -1;
    }

    size_t len = strlen(s);
    if (len == 0 || (len % 2) != 0) {
        return -1;
    }

    int openCount = 0;
    int closeCount = 0;
    int imbalance = 0;
    int swaps = 0;

    for (size_t i = 0; i < len; i++) {
        if (s[i] == '[') {
            openCount++;
            if (imbalance > 0) {
                swaps += imbalance;
                imbalance--;
            }
        } else if (s[i] == ']') {
            closeCount++;
            imbalance = closeCount - openCount;
        } else {
            return -1;
        }
    }

    if (openCount != closeCount) {
        return -1;
    }

    return swaps;
}

int main(void) {
    const char *testCases[] = {
        "[]][][",
        "]]][[[",
        "[[][]]",
        "][",
        "[]",
        "]]][[[]]",
        NULL
    };

    for (int i = 0; testCases[i] != NULL; i++) {
        int result = minSwapsToBalance(testCases[i]);
        if (result >= 0) {
            printf("Input: %s -> Minimum swaps: %d\n", testCases[i], result);
        } else {
            printf("Input: %s -> Cannot be balanced\n", testCases[i]);
        }
    }

    return 0;
}