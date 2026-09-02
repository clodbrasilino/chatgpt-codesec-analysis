#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} ItemCount;

int find_most_frequent(const int *arr, int size, int *result) {
    if (arr == NULL || size <= 0 || result == NULL) {
        return -1;
    }

    ItemCount *counts = (ItemCount *)malloc(size * sizeof(ItemCount));
    if (counts == NULL) {
        return -1;
    }

    int unique_count = 0;
    int i, j;

    for (i = 0; i < size; i++) {
        int found = 0;
        for (j = 0; j < unique_count; j++) {
            if (counts[j].value == arr[i]) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            counts[unique_count].value = arr[i];
            counts[unique_count].count = 1;
            unique_count++;
        }
    }

    int max_count = 0;
    int max_index = 0;
    for (i = 0; i < unique_count; i++) {
        if (counts[i].count > max_count) {
            max_count = counts[i].count;
            max_index = i;
        }
    }

    *result = counts[max_index].value;
    free(counts);
    return 0;
}

int main(void) {
    int arr[] = {1, 3, 2, 3, 4, 3, 2, 2, 2, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result;

    if (find_most_frequent(arr, size, &result) == 0) {
        printf("%d\n", result);
    }

    return 0;
}