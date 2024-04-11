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
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'records' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        records[i].a = i;
        records[i].b = i * 2;
    }

    Tuple* rearElement = extractRearElement(records, size);
    if (rearElement != NULL) {
        /* Possible weaknesses found:
         *  use of uninitialized value '*rearElement.b' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        printf("Rear element: (%d, %d)\n", rearElement->a, rearElement->b);
    } else {
        printf("No rear element found.\n");
    }

    free(records);
    return 0;
}