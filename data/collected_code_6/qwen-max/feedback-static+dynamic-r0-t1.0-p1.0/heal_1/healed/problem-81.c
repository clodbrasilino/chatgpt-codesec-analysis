#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* zip_tuples(const Tuple* t1, const Tuple* t2, size_t n, Tuple** result) {
    *result = (Tuple*)malloc(n * sizeof(Tuple));
    if (*result == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < n; ++i) {
        (*result)[i].a = t1[i].a + t2[i].a;
        (*result)[i].b = t1[i].b + t2[i].b;
    }
    return *result;
}

void free_tuples(Tuple* t) {
    free(t);
}

int main() {
    size_t n = 3;
    const Tuple t1[3] = {{1, 2}, {3, 4}, {5, 6}};
    const Tuple t2[3] = {{7, 8}, {9, 10}, {11, 12}};
    Tuple* zipped = NULL;

    if (zip_tuples(t1, t2, n, &zipped)) {
        for (size_t i = 0; i < n; ++i) {
            printf("(%d, %d)\n", zipped[i].a, zipped[i].b);
        }
        free_tuples(zipped);
    } else {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }

    return 0;
}