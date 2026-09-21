#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isUndulating(int num) {
    if (num < 100) {
        return false;
    }

    int length = snprintf(NULL, 0, "%d", num);
    if (length < 0) {
        return false;
    }

    char *str = (char *)malloc((size_t)length + 1);
    if (str == NULL) {
        return false;
    }

    if (snprintf(str, (size_t)length + 1, "%d", num) < 0) {
        free(str);
        return false;
    }

    if (str[0] == str[1]) {
        free(str);
        return false;
    }

    for (int i = 2; i < length; i++) {
        if (str[i] != str[i - 2]) {
            free(str);
            return false;
        }
    }

    free(str);
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