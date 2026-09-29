#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isUndulating(int num) {
    if (num < 100) {
        return false;
    }

    int curr = num % 10;
    num /= 10;
    int prev = num % 10;

    if (curr == prev) {
        return false;
    }

    num /= 10;

    while (num > 0) {
        int next = num % 10;
        if (next != curr) {
            return false;
        }
        curr = prev;
        prev = next;
        num /= 10;
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