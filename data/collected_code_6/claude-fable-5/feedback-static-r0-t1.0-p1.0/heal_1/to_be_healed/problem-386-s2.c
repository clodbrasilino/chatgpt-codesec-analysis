#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long min_swaps_for_balance(const char *str);

long min_swaps_for_balance(const char *str)
{
    long open_count = 0;
    long close_count = 0;
    long swaps = 0;
    long imbalance = 0;
    size_t i;
    size_t len;

    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

    for (i = 0; i < len; i++) {
        if (str[i] == '[') {
            open_count++;
        } else if (str[i] == ']') {
            close_count++;
        } else {
            return -1;
        }
    }

    if (open_count != close_count) {
        return -1;
    }

    open_count = 0;
    close_count = 0;

    for (i = 0; i < len; i++) {
        if (str[i] == '[') {
            open_count++;
            if (imbalance > 0) {
                swaps += imbalance;
                imbalance--;
            }
        } else {
            close_count++;
            imbalance = close_count - open_count;
        }
    }

    return swaps;
}

int main(void)
{
    const char *test1 = "[]][][";
    const char *test2 = "[[][]]";
    const char *test3 = "]]][[[";
    long result;

    result = min_swaps_for_balance(test1);
    if (result < 0) {
        if (fprintf(stderr, "Invalid input: %s\n", test1) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("String: %s -> Minimum swaps: %ld\n", test1, result) < 0) {
            return EXIT_FAILURE;
        }
    }

    result = min_swaps_for_balance(test2);
    if (result < 0) {
        if (fprintf(stderr, "Invalid input: %s\n", test2) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("String: %s -> Minimum swaps: %ld\n", test2, result) < 0) {
            return EXIT_FAILURE;
        }
    }

    result = min_swaps_for_balance(test3);
    if (result < 0) {
        if (fprintf(stderr, "Invalid input: %s\n", test3) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("String: %s -> Minimum swaps: %ld\n", test3, result) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}