#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int a;
    int b;
} Tuple;

Tuple* extractRearElement(Tuple* records, int size) {
    if (size <= 0) {
        return NULL;
    }
    return &records[size - 1];
}

int main() {
    int size = 5;
    Tuple* records = (Tuple*)malloc(size * sizeof(Tuple));
    for (int i = 0; i < size; i++) {
        records[i].a = i;
        records[i].b = i * 2;
    }

    Tuple* rearElement = extractRearElement(records, size);
    if (rearElement != NULL) {
        printf("Rear element: (%d, %d)\n", rearElement->a, rearElement->b);
    } else {
        printf("No rear element found.\n");
    }

    free(records);
    return 0;
}