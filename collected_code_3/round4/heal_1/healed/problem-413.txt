#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple* extractNthElement(Tuple* list, int size, int n) {
    if (!list || n < 0 || n >= size) {
        return NULL;
    }
    return &list[n];
}

int main() {
    int size = 5;
    Tuple* list = malloc(sizeof(Tuple) * size);
    if (list == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    for (int i = 0; i < size; i++) {
        list[i].first = i;
        list[i].second = i * 2;
    }

    int n = 3;
    Tuple* nthElement = extractNthElement(list, size, n);
    if (nthElement != NULL) {
        printf("The %dth element is (%d, %d)\n", n, nthElement->first, nthElement->second);
    } else {
        printf("Invalid index\n");
    }

    free(list);
    return 0;
}