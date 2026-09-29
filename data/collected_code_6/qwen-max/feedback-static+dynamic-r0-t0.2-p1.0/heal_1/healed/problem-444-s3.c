#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

void trim_tuple(Tuple *t, int k) {
    if (k >= 0 && t->length > 0) {
        size_t new_length = t->length - k;
        t->length = (new_length > 0) ? new_length : 0;
    }
}

int main() {
    Tuple tuples[] = {
        { .data = (int[]){1, 2, 3, 4, 5}, .length = 5 },
        { .data = (int[]){6, 7, 8, 9, 10}, .length = 5 },
        { .data = (int[]){11, 12, 13, 14, 15}, .length = 5 }
    };
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    int k = 2;

    for (size_t i = 0; i < num_tuples; ++i) {
        trim_tuple(&tuples[i], k);
        for (size_t j = 0; j < tuples[i].length; ++j) {
            printf("%d ", tuples[i].data[j]);
        }
        printf("\n");
    }

    return 0;
}