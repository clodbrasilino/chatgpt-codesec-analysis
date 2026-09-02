#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} ItemCount;

int compare(const void *a, const void *b) {
    return ((ItemCount *)a)->count - ((ItemCount *)b)->count;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int findMaxFrequency(int *arr, int n, int *maxValue, int *maxCount) {
    if (n == 0) return -1;
    ItemCount *items = (ItemCount *)calloc(n, sizeof(ItemCount));
    if (items == NULL) return -1;

    for (int i = 0; i < n; ++i) {
        items[i].value = arr[i];
        items[i].count = 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[i] == arr[j]) {
                items[i].count++;
                items[j].value = -1;
            }
        }
    }

    qsort(items, n, sizeof(ItemCount), compare);

    for (int i = n - 1; i >= 0; --i) {
        if (items[i].value != -1) {
            *maxValue = items[i].value;
            *maxCount = items[i].count;
            free(items);
            return 0;
        }
    }

    free(items);
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 2, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxValue, maxCount;

    if (findMaxFrequency(arr, n, &maxValue, &maxCount) == 0) {
        printf("Item with maximum frequency: %d, Frequency: %d\n", maxValue, maxCount);
    } else {
        printf("Failed to find the item with maximum frequency.\n");
    }

    return 0;
}