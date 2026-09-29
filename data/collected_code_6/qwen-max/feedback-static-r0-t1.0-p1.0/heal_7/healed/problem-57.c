#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int compare(const void *a, const void *b) {
    char temp1[22];
    char temp2[22];
    snprintf(temp1, sizeof(temp1), "%d%d", *(const int *)a, *(const int *)b);
    snprintf(temp2, sizeof(temp2), "%d%d", *(const int *)b, *(const int *)a);
    return strcmp(temp1, temp2) < 0 ? -1 : 1;
}

char* largestNumber(const int *digits, int size) {
    int *sorted_digits = (int *)malloc(size * sizeof(int));
    if (sorted_digits == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        sorted_digits[i] = digits[i];
    }

    qsort(sorted_digits, size, sizeof(int), compare);

    int result_size = 0;
    for (int i = 0; i < size; ++i) {
        char str[12];
        snprintf(str, sizeof(str), "%d", sorted_digits[i]);
        result_size += strlen(str);
    }
    result_size++; // Add 1 for the null terminator

    char *result = (char *)malloc(result_size);
    if (result == NULL) {
        free(sorted_digits);
        return NULL;
    }
    result[0] = '\0';
    for (int i = 0; i < size; ++i) {
        char str[12];
        snprintf(str, sizeof(str), "%d", sorted_digits[i]);
        strcat(result, str);
    }

    free(sorted_digits);
    return result;
}

int main() {
    const int digits[] = {3, 30, 34, 5, 9};
    int size = 5;
    char *result = largestNumber(digits, size);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}