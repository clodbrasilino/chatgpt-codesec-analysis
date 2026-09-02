#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Item;

int compare(const void *a, const void *b) {
    return ((Item *)a)->count - ((Item *)b)->count;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int findMaxFrequency(int *arr, int n, int *maxValue, int *maxCount) {
    if (n <= 0) return -1;
    Item *items = (Item *)malloc(n * sizeof(Item));
    if (!items) return -1;
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
    int arr[] = {1, 2, 3, 2, 4, 2, 5, 1, 6, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxValue, maxCount;
    if (findMaxFrequency(arr, n, &maxValue, &maxCount) == 0) {
        printf("Max Frequency: %d, Value: %d\n", maxCount, maxValue);
    } else {
        printf("Error occurred.\n");
    }
    return 0;
}