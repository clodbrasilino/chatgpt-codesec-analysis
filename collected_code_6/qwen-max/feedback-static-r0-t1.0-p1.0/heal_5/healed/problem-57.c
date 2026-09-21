#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    char temp1[22], temp2[22];
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

    char *result = (char *)malloc((size * 11 + 1) * sizeof(char));
    if (result == NULL) {
        free(sorted_digits);
        return NULL;
    }
    result[0] = '\0';
    for (int i = 0; i < size; ++i) {
        char str[12];
        snprintf(str, sizeof(str), "%d", sorted_digits[i]);
        strncat(result, str, 11);
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