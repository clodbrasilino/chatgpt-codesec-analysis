#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

int nextBiggerNumber(int num) {
    char str[11];
    int i, j;
    strcpy(str, "");
    sprintf(str, "%d", num);

    int len = strlen(str);
    for (i = len - 2; i >= 0; --i) {
        if (str[i] < str[i + 1]) {
            break;
        }
    }
    if (i == -1) {
        return -1;
    }

    for (j = len - 1; j > i; --j) {
        if (str[j] > str[i]) {
            char temp = str[i];
            str[i] = str[j];
            str[j] = temp;
            break;
        }
    }

    qsort(str + i + 1, len - i - 1, sizeof(char), compare);

    return atoi(str);
}

int main() {
    int num = 12345;
    int result = nextBiggerNumber(num);
    if (result != -1) {
        printf("Next bigger number: %d\n", result);
    } else {
        printf("No bigger number can be formed.\n");
    }
    return 0;
}