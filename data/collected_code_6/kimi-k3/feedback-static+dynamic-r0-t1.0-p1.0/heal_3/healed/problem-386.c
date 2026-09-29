#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

int minSwaps(const char *str, size_t max_len) {
    int imbalance = 0;
    int swaps = 0;
    size_t i;
    size_t len;

    if (str == NULL) {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len == max_len) {
        return -1;
    }

    if (len % 2 != 0) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        if (str[i] == '[') {
            imbalance++;
        } else if (str[i] == ']') {
            if (imbalance == 0) {
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
    size_t len;
    int result;

    len = strnlen(test1, 7);
    result = minSwaps(test1, len + 1);
    printf("Input: %s | Minimum swaps: %d\n", test1, result);

    len = strnlen(test2, 7);
    result = minSwaps(test2, len + 1);
    printf("Input: %s | Minimum swaps: %d\n", test2, result);

    len = strnlen(test3, 7);
    result = minSwaps(test3, len + 1);
    printf("Input: %s | Minimum swaps: %d\n", test3, result);

    len = strnlen(test4, 3);
    result = minSwaps(test4, len + 1);
    printf("Input: %s | Minimum swaps: %d\n", test4, result);

    len = strnlen(test5, 9);
    result = minSwaps(test5, len + 1);
    printf("Input: %s | Minimum swaps: %d\n", test5, result);

    return 0;
}