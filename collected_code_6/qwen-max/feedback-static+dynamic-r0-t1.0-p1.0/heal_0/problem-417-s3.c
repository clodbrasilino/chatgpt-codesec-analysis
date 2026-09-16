#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int findCommonFirstElement(Tuple *tuples, int size) {
    if (size == 0) return -1;
    int first = tuples[0].first;
    for (int i = 1; i < size; i++) {
        if (tuples[i].first != first) return -1;
    }
    return first;
}

int main() {
    Tuple tuples[] = {{1, 2}, {1, 3}, {1, 4}};
    int size = sizeof(tuples) / sizeof(tuples[0]);
    int result = findCommonFirstElement(tuples, size);
    if (result != -1) {
        printf("Common first element: %d\n", result);
    } else {
        printf("No common first element found.\n");
    }
    return 0;
}