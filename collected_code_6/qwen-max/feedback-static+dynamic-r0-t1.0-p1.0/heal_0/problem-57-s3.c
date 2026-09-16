#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

char* formLargestNumber(int digits[], int size) {
    char *result = (char *)malloc((size + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    qsort(digits, size, sizeof(int), compare);
    for (int i = 0; i < size; ++i) {
        result[i] = digits[i] + '0';
    }
    result[size] = '\0';
    return result;
}

int main() {
    int digits[] = {3, 5, 1, 4, 2};
    int size = sizeof(digits) / sizeof(digits[0]);
    char *largestNumber = formLargestNumber(digits, size);
    if (largestNumber != NULL) {
        printf("The largest number is: %s\n", largestNumber);
        free(largestNumber);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}