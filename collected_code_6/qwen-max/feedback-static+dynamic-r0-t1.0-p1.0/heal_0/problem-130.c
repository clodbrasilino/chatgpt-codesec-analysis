#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} ItemFreq;

int compare(const void *a, const void *b) {
    return ((ItemFreq *)b)->count - ((ItemFreq *)a)->count;
}

ItemFreq* findMaxFrequency(int *arr, int n, int *maxCount) {
    ItemFreq *freq = (ItemFreq *)calloc(n, sizeof(ItemFreq));
    if (freq == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; ++i) {
        freq[i].value = arr[i];
        freq[i].count = 1;
        for (int j = 0; j < i; ++j) {
            if (arr[i] == arr[j]) {
                freq[i].count = 0;
                break;
            }
        }
    }

    qsort(freq, n, sizeof(ItemFreq), compare);

    int k = 0;
    while (k < n && freq[k].count > 0) {
        k++;
    }

    ItemFreq *result = (ItemFreq *)realloc(freq, k * sizeof(ItemFreq));
    if (result == NULL) {
        free(freq);
        return NULL;
    }

    *maxCount = result[0].count;
    return result;
}

int main() {
    int arr[] = {1, 3, 2, 1, 2, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxCount;

    ItemFreq *result = findMaxFrequency(arr, n, &maxCount);
    if (result != NULL && maxCount > 0) {
        printf("Max frequency item: %d, Count: %d\n", result[0].value, result[0].count);
        free(result);
    } else {
        printf("No items found.\n");
    }

    return 0;
}