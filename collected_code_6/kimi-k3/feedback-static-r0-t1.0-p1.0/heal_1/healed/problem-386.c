#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int minSwaps(const char *str, size_t max_len) {
    int imbalance = 0;
    int swaps = 0;
    size_t i;
    size_t len = 0;

    if (str == NULL) {
        return -1;
    }

    while (len < max_len && str[len] != '\0') {
        len++;
    }

    if (len == max_len && str[len] != '\0') {
        return -1;
    }

    if (len % 2 != 0) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        if (str[i] == '[') {
            if (imbalance == INT_MAX) {
                return -1;
            }
            imbalance++;
        } else if (str[i] == ']') {
            if (imbalance == 0) {
                if (swaps == INT_MAX) {
                    return -1;
                }
                swaps++;
            } else {
                imbalance--;
            }
        } else {
            return -1;
        }
    }

    if (imbalance != 0) {
        return -1;
    }

    return swaps;
}

int main(void) {
    const char *test1 = "[]][][";
    const char *test2 = "[[][]]";
    const char *test3 = "]]][[[";
    const char *test4 = "][";
    const char *test5 = "[[[[]]]]";
    const size_t max_len = 1024;
    int result;

    result = minSwaps(test1, max_len);
    printf("Input: %s | Minimum swaps: %d\n", test1, result);

    result = minSwaps(test2, max_len);
    printf("Input: %s | Minimum swaps: %d\n", test2, result);

    result = minSwaps(test3, max_len);
    printf("Input: %s | Minimum swaps: %d\n", test3, result);

    result = minSwaps(test4, max_len);
    printf("Input: %s | Minimum swaps: %d\n", test4, result);

    result = minSwaps(test5, max_len);
    printf("Input: %s | Minimum swaps: %d\n", test5, result);

    return 0;
}