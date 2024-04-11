#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple* extractNthElement(Tuple* list, int size, int n) {
    if (n < 0 || n >= size) {
        return NULL;
    }
    return &list[n];
}

int main() {
    int size = 5;
    Tuple* list = malloc(sizeof(Tuple) * size);
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'list' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        list[i].first = i;
        list[i].second = i * 2;
    }

    int n = 3;
    Tuple* nthElement = extractNthElement(list, size, n);
    if (nthElement != NULL) {
        /* Possible weaknesses found:
         *  use of uninitialized value '*nthElement.second' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        printf("The %dth element is (%d, %d)\n", n, nthElement->first, nthElement->second);
    } else {
        printf("Invalid index\n");
    }

    free(list);
    return 0;
}