#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int compare(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

int nextBiggerNumber(int num) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[11];
    
    snprintf(str, sizeof(str), "%d", num);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    int i;
    for (i = len - 2; i >= 0 && str[i] >= str[i + 1]; --i) {
    }

    if (i == -1) {
        return -1;
    }

    for (int j = len - 1; j > i; --j) {
        if (str[j] > str[i]) {
            char temp = str[i];
            str[i] = str[j];
            str[j] = temp;
            break;
        }
    }

    qsort(str + i + 1, len - i - 1, sizeof(char), compare);

    long result = strtol(str, NULL, 10);
    if (result > INT_MAX || result < INT_MIN) {
        return -1;
    }
    return (int)result;
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