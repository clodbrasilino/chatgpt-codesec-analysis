#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

int minSwapsToBalance(const char *s, size_t max_len) {
    if (s == NULL || max_len == 0) {
        return -1;
    }

    size_t len = strnlen(s, max_len);
    if (len == 0 || len == max_len || (len % 2) != 0) {
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
    size_t max_len = 1024;

    for (int i = 0; testCases[i] != NULL; i++) {
        int result = minSwapsToBalance(testCases[i], max_len);
        if (result >= 0) {
            printf("Input: %s -> Minimum swaps: %d\n", testCases[i], result);
        } else {
            printf("Input: %s -> Cannot be balanced\n", testCases[i]);
        }
    }

    return 0;
}