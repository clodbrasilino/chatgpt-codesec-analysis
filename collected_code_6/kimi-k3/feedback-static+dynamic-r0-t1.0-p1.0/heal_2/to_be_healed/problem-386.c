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
    if (len == max_len && str[len] != '\0') {
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
    int result;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    result = minSwaps(test1, strlen(test1) + 1);
    printf("Input: %s | Minimum swaps: %d\n", test1, result);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    result = minSwaps(test2, strlen(test2) + 1);
    printf("Input: %s | Minimum swaps: %d\n", test2, result);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    result = minSwaps(test3, strlen(test3) + 1);
    printf("Input: %s | Minimum swaps: %d\n", test3, result);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    result = minSwaps(test4, strlen(test4) + 1);
    printf("Input: %s | Minimum swaps: %d\n", test4, result);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    result = minSwaps(test5, strlen(test5) + 1);
    printf("Input: %s | Minimum swaps: %d\n", test5, result);

    return 0;
}