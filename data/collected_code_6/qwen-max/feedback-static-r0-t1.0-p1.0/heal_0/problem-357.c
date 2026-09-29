#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int element;
} Tuple;

int findMaxElement(Tuple *tuples, size_t count) {
    if (count == 0) return 0;
    int max = tuples[0].element;
    for (size_t i = 1; i < count; ++i) {
        if (tuples[i].element > max) {
            max = tuples[i].element;
        }
    }
    return max;
}

int main() {
    Tuple tuples[] = {{5}, {3}, {9}, {7}, {2}};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    int maxElement = findMaxElement(tuples, count);
    printf("The maximum element is: %d\n", maxElement);
    return 0;
}