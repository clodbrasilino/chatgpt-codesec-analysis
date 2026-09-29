#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

char* largestNumber(int* digits, int n) {
    qsort(digits, n, sizeof(int), compare);
    char* result = (char*)malloc((n + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        result[i] = digits[i] + '0';
    }
    result[n] = '\0';
    return result;
}

int main() {
    int digits[] = {3, 30, 34, 5, 9};
    int n = sizeof(digits) / sizeof(digits[0]);
    char* result = largestNumber(digits, n);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}