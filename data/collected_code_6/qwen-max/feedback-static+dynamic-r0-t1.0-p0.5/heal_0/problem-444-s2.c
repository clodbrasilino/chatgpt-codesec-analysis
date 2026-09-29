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
    Tuple t = { .data = (int[]){1, 2, 3, 4, 5}, .length = 5 };
    int k = 2;

    trim_tuple(&t, k);

    for (size_t i = 0; i < t.length; ++i) {
        printf("%d ", t.data[i]);
    }

    free(t.data);
    return 0;
}