#include <stdio.h>

void tupleAccess(const int* tuple, int size) {
    int first = tuple[0];
    int last = tuple[size - 1];
    printf("Initial data: %d\n", first);
    printf("Last data: %d\n", last);
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    tupleAccess(tuple, size);
    return 0;
}