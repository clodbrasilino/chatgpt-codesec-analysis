#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

int count_repeated_items(Tuple t) {
    int *counts = (int *)calloc(t.length, sizeof(int));
    if (counts == NULL) {
        return -1;
    }
    for (size_t i = 0; i < t.length; ++i) {
        for (size_t j = i + 1; j < t.length; ++j) {
            if (t.data[i] == t.data[j]) {
                counts[i]++;
                break;
            }
        }
    }
    int repeated = 0;
    for (size_t i = 0; i < t.length; ++i) {
        if (counts[i] > 0) {
            repeated++;
        }
    }
    free(counts);
    return repeated;
}

int main() {
    int data[] = {1, 2, 3, 2, 4, 5, 3, 1};
    Tuple t = {data, 8};
    int result = count_repeated_items(t);
    printf("Number of repeated items: %d\n", result);
    return 0;
}