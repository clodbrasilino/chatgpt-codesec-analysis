#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} ValueCount;

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

ValueCount findMaxOccurrence(int *arr, int n) {
    if (n <= 0) return (ValueCount){-1, 0};

    qsort(arr, n, sizeof(int), compare);

    ValueCount max = {arr[0], 1};
    int currentCount = 1;

    for (int i = 1; i < n; ++i) {
        if (arr[i] == arr[i - 1]) {
            currentCount++;
        } else {
            if (currentCount > max.count) {
                max.value = arr[i - 1];
                max.count = currentCount;
            }
            currentCount = 1;
        }
    }

    if (currentCount > max.count) {
        max.value = arr[n - 1];
        max.count = currentCount;
    }

    return max;
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 2, 3, 4, 5, 4, 4, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    ValueCount max = findMaxOccurrence(arr, n);

    printf("Value: %d, Count: %d\n", max.value, max.count);

    return 0;
}