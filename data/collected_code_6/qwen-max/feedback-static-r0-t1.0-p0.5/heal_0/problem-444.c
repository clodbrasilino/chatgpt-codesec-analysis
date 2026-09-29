#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

void trim_tuple(Tuple *t, int k) {
    if (k >= 0 && t->length > k) {
        t->length -= k;
        t->data = realloc(t->data, t->length * sizeof(int));
    }
}

int main() {
    Tuple t1 = { .data = (int[]){1, 2, 3, 4, 5}, .length = 5 };
    Tuple t2 = { .data = (int[]){6, 7, 8, 9, 10, 11, 12}, .length = 7 };

    int k = 2;

    trim_tuple(&t1, k);
    trim_tuple(&t2, k);

    for (size_t i = 0; i < t1.length; ++i) {
        printf("%d ", t1.data[i]);
    }
    printf("\n");

    for (size_t i = 0; i < t2.length; ++i) {
        printf("%d ", t2.data[i]);
    }
    printf("\n");

    free(t1.data);
    free(t2.data);

    return 0;
}