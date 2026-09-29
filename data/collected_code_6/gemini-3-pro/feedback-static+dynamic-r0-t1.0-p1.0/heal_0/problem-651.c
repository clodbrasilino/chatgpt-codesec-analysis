#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

bool is_subset(const Tuple *tuple_a, const Tuple *tuple_b) {
    if (!tuple_a || !tuple_b || !tuple_a->elements || !tuple_b->elements) {
        return false;
    }

    if (tuple_a->size == 0) {
        return true;
    }

    if (tuple_b->size == 0) {
        return false;
    }

    for (size_t i = 0; i < tuple_a->size; i++) {
        bool found = false;
        for (size_t j = 0; j < tuple_b->size; j++) {
            if (tuple_a->elements[i] == tuple_b->elements[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int elements_a[] = {1, 2, 3};
    Tuple tuple_a = {elements_a, 3};

    int elements_b[] = {1, 2, 3, 4, 5};
    Tuple tuple_b = {elements_b, 5};

    int elements_c[] = {1, 6};
    Tuple tuple_c = {elements_c, 2};

    if (is_subset(&tuple_a, &tuple_b)) {
        printf("Tuple A is a subset of Tuple B\n");
    } else {
        printf("Tuple A is not a subset of Tuple B\n");
    }

    if (is_subset(&tuple_c, &tuple_b)) {
        printf("Tuple C is a subset of Tuple B\n");
    } else {
        printf("Tuple C is not a subset of Tuple B\n");
    }

    return 0;
}