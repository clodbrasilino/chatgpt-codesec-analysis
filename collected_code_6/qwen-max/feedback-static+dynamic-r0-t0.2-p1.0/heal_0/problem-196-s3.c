#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

void free_tuple(Tuple *t) {
    free(t->data);
    t->data = NULL;
    t->length = 0;
}

int main() {
    Tuple tuples[] = {{.data = (int[]){1, 2, 3}, .length = 3},
                      {.data = (int[]){4, 5}, .length = 2},
                      {.data = (int[]){6, 7, 8, 9}, .length = 4},
                      {.data = (int[]){10, 11, 12}, .length = 3}};
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    size_t k = 3;

    for (size_t i = 0; i < num_tuples; ) {
        if (tuples[i].length == k) {
            for (size_t j = i + 1; j < num_tuples; ++j) {
                tuples[j - 1] = tuples[j];
            }
            --num_tuples;
            free_tuple(&tuples[num_tuples]);
        } else {
            ++i;
        }
    }

    for (size_t i = 0; i < num_tuples; ++i) {
        for (size_t j = 0; j < tuples[i].length; ++j) {
            printf("%d ", tuples[i].data[j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < num_tuples; ++i) {
        free_tuple(&tuples[i]);
    }

    return 0;
}