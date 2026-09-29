#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

int compare(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

long long findNextGreaterNumber(long long num) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char numStr[21];
    snprintf(numStr, sizeof(numStr), "%lld", num);
    int len = (int)strnlen(numStr, sizeof(numStr));
    int i, j;

    for (i = len - 2; i >= 0; --i) {
        if (numStr[i] < numStr[i + 1]) {
            break;
        }
    }

    if (i == -1) {
        return -1;
    }

    for (j = len - 1; j > i; --j) {
        if (numStr[j] > numStr[i]) {
            char temp = numStr[i];
            numStr[i] = numStr[j];
            numStr[j] = temp;
            break;
        }
    }

    qsort(&numStr[i + 1], len - i - 1, 1, compare);

    long long result = atoll(numStr);
    if (result <= num || result > LLONG_MAX) {
        return -1;
    }
    return result;
}

int main() {
    long long num = 12345;
    long long nextNum = findNextGreaterNumber(num);
    if (nextNum == -1) {
        printf("No bigger number can be formed.\n");
    } else {
        printf("The next bigger number is: %lld\n", nextNum);
    }
    return 0;
}