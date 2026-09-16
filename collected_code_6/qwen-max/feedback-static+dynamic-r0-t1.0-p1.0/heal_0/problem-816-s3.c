#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

void clear_tuples(Tuple *tuples, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        tuples[i].a = 0;
        tuples[i].b = 0;
    }
}

int main() {
    size_t count = 5;
    Tuple *tuples = (Tuple *)malloc(count * sizeof(Tuple));
    if (tuples == NULL) {
        return 1;
    }

    for (size_t i = 0; i < count; ++i) {
        tuples[i].a = i;
        tuples[i].b = i * 2;
    }

    clear_tuples(tuples, count);

    for (size_t i = 0; i < count; ++i) {
        printf("Tuple %zu: (%d, %d)\n", i, tuples[i].a, tuples[i].b);
    }

    free(tuples);
    return 0;
}