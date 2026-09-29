#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

int hasAllKElements(Tuple tuple, int k) {
    if (tuple.elements == NULL || tuple.size <= 0) {
        return 0;
    }
    for (int i = 0; i < tuple.size; i++) {
        if (tuple.elements[i] != k) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int k = 5;
    int elements[] = {5, 5, 5, 5, 5};
    Tuple tuple = {elements, 5};

    if (hasAllKElements(tuple, k)) {
        printf("All elements are %d\n", k);
    } else {
        printf("Not all elements are %d\n", k);
    }

    return 0;
}