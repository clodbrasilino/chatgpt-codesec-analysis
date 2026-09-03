#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Item;

int compare(const void *a, const void *b) {
    return ((Item *)b)->count - ((Item *)a)->count;
}

int findMaxFrequency(const int *arr, int n, int *maxValue, int *maxCount) {
    if (n <= 0) return -1;
    Item *items = (Item *)malloc(n * sizeof(Item));
    if (items == NULL) return -1;

    for (int i = 0; i < n; ++i) {
        items[i].value = arr[i];
        items[i].count = 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (items[i].value == items[j].value) {
                items[i].count++;
                items[j].value = -1;
            }
        }
    }

    qsort(items, n, sizeof(Item), compare);

    for (int i = 0; i < n; ++i) {
        if (items[i].value != -1) {
            *maxValue = items[i].value;
            *maxCount = items[i].count;
            break;
        }
    }

    free(items);
    return 0;
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 2, 5, 3, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxValue, maxCount;

    if (findMaxFrequency(arr, n, &maxValue, &maxCount) == 0) {
        printf("Max frequency item: %d, Count: %d\n", maxValue, maxCount);
    } else {
        printf("Error occurred.\n");
    }

    return 0;
}