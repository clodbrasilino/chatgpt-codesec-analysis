#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

int count_repeated_items(Tuple t) {
    if (t.length == 0) return 0;
    int *counts = (int *)calloc(t.length, sizeof(int));
    for (size_t i = 0; i < t.length; ++i) {
        counts[t.data[i]]++;
    }
    int repeated_count = 0;
    for (size_t i = 0; i < t.length; ++i) {
        if (counts[t.data[i]] > 1) {
            repeated_count += counts[t.data[i]];
            counts[t.data[i]] = 0;
        }
    }
    free(counts);
    return repeated_count / 2;
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 4, 5, 1};
    Tuple t = {arr, sizeof(arr) / sizeof(arr[0])};
    int result = count_repeated_items(t);
    printf("Number of repeated items: %d\n", result);
    return 0;
}