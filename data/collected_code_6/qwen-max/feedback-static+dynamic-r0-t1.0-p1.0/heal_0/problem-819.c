#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} ElementCount;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

ElementCount* countConsecutiveDuplicates(int *arr, int size, int *countSize) {
    if (size == 0) return NULL;

    qsort(arr, size, sizeof(int), compare);

    ElementCount *result = (ElementCount *)malloc(size * sizeof(ElementCount));
    if (result == NULL) exit(1);

    int index = 0;
    result[index].value = arr[0];
    result[index].count = 1;

    for (int i = 1; i < size; ++i) {
        if (arr[i] == arr[i-1]) {
            result[index].count++;
        } else {
            result[++index].value = arr[i];
            result[index].count = 1;
        }
    }

    *countSize = index + 1;
    return result;
}

int main() {
    int arr[] = {1, 1, 2, 3, 3, 3, 4, 4, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int countSize;

    ElementCount *result = countConsecutiveDuplicates(arr, size, &countSize);

    for (int i = 0; i < countSize; ++i) {
        printf("%d: %d\n", result[i].value, result[i].count);
    }

    free(result);
    return 0;
}