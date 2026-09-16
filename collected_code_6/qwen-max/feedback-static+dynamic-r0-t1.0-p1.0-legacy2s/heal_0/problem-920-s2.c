#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int is_all_none(const Tuple *tuple) {
    return (tuple->a == 0 && tuple->b == 0);
}

void remove_all_none_tuples(Tuple **list, int *size) {
    int new_size = 0;
    for (int i = 0; i < *size; ++i) {
        if (!is_all_none(&(*list)[i])) {
            (*list)[new_size++] = (*list)[i];
        }
    }
    *size = new_size;
}

int main() {
    Tuple *tuples;
    int size = 5;
    tuples = malloc(size * sizeof(Tuple));

    tuples[0] = (Tuple){1, 2};
    tuples[1] = (Tuple){0, 0};
    tuples[2] = (Tuple){3, 4};
    tuples[3] = (Tuple){0, 0};
    tuples[4] = (Tuple){5, 6};

    remove_all_none_tuples(&tuples, &size);

    for (int i = 0; i < size; ++i) {
        printf("(%d, %d)\n", tuples[i].a, tuples[i].b);
    }

    free(tuples);
    return 0;
}