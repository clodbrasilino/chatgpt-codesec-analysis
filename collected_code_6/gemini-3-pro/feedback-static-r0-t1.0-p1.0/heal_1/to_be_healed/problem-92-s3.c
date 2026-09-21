#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isUndulating(int num) {
    if (num < 100) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[15];
    int length = snprintf(str, sizeof(str), "%d", num);

    if (length < 0 || length >= (int)sizeof(str)) {
        return false;
    }

    if (str[0] == str[1]) {
        return false;
    }

    for (int i = 2; i < length; i++) {
        if (str[i] != str[i - 2]) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int testCases[] = {121, 1212, 12121, 122, 12, 101, 1010};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        if (isUndulating(testCases[i])) {
            printf("%d is undulating.\n", testCases[i]);
        } else {
            printf("%d is not undulating.\n", testCases[i]);
        }
    }

    return EXIT_SUCCESS;
}