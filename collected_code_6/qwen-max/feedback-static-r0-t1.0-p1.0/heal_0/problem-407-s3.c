#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

long long findNextGreaterNumber(long long num) {
    char numStr[20];
    sprintf(numStr, "%lld", num);
    int len = strlen(numStr);
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

    qsort(numStr + i + 1, len - i - 1, 1, compare);

    return atoll(numStr);
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