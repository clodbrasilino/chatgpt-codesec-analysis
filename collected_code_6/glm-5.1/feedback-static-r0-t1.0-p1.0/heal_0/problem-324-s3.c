#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int* extract_alternate_chain_sums(Tuple* tuples, size_t count, size_t* out_size) {
    if (tuples == NULL || out_size == NULL || count == 0) {
        if (out_size != NULL) {
            *out_size = 0;
        }
        return NULL;
    }

    *out_size = (count + 1) / 2;
    int* sums = (int*)malloc(*out_size * sizeof(int));
    if (sums == NULL) {
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < *out_size; i++) {
        sums[i] = tuples[i * 2].a + tuples[i * 2].b;
    }

    return sums;
}

int main() {
    Tuple data[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    size_t count = sizeof(data) / sizeof(data[0]);
    size_t out_size = 0;

    int* sums = extract_alternate_chain_sums(data, count, &out_size);

    if (sums != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%d\n", sums[i]);
        }
        free(sums);
    }

    return 0;
}