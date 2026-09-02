#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} ItemCount;

int compare(const void *a, const void *b) {
    return ((ItemCount *)b)->count - ((ItemCount *)a)->count;
}

int findMaxFrequency(int *arr, int n, int *maxValue, int *maxCount) {
    if (n <= 0) return -1;
    ItemCount *items = (ItemCount *)malloc(n * sizeof(ItemCount));
    if (items == NULL) return -1;

    for (int i = 0; i < n; ++i) {
        items[i].value = arr[i];
        items[i].count = 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] == arr[i]) {
                items[i].count++;
                arr[j] = -1;
            }
        }
    }

    qsort(items, n, sizeof(ItemCount), compare);

    *maxValue = items[0].value;
    *maxCount = items[0].count;

    free(items);
    return 0;
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 2, 3, 3, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxValue, maxCount;

    if (findMaxFrequency(arr, n, &maxValue, &maxCount) == 0) {
        printf("Item with maximum frequency: %d, Frequency: %d\n", maxValue, maxCount);
    } else {
        printf("Error occurred.\n");
    }

    return 0;
}