#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int count_bidirectional_pairs(const Tuple *tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        return 0;
    }

    int count = 0;

    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if ((tuples[i].a == tuples[j].b && tuples[i].b == tuples[j].a)) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    Tuple arr[] = {{1, 2}, {3, 4}, {2, 1}, {5, 6}, {4, 3}, {7, 8}};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int result = count_bidirectional_pairs(arr, size);

    printf("%d\n", result);

    return 0;
}