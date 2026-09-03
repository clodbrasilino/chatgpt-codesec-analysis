#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} TupleList;

int check_k_elements(TupleList list, int k) {
    if (list.size != k) {
        return 0;
    }
    for (size_t i = 0; i < list.size; ++i) {
        if (list.elements[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int elements[] = {1, 2, 3};
    TupleList list = {elements, 3};

    int k = 3;
    if (check_k_elements(list, k)) {
        printf("The tuple list has all %d elements.\n", k);
    } else {
        printf("The tuple list does not have all %d elements.\n", k);
    }

    return 0;
}