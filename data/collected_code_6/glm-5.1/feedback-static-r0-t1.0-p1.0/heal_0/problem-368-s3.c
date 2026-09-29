#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple *repeat_tuple(const Tuple *input, size_t n) {
    if (input == NULL || input->size == 0) {
        return NULL;
    }

    size_t new_size;
    if (__builtin_mul_overflow(input->size, n, &new_size)) {
        return NULL;
    }

    Tuple *result = (Tuple *)malloc(sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    result->size = new_size;

    if (new_size == 0) {
        result->elements = NULL;
        return result;
    }

    result->elements = (int *)malloc(new_size * sizeof(int));
    if (result->elements == NULL) {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < input->size; ++j) {
            result->elements[(i * input->size) + j] = input->elements[j];
        }
    }

    return result;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->elements);
        free(t);
    }
}

int main(void) {
    Tuple input;
    int data[] = {1, 2, 3};
    input.elements = data;
    input.size = sizeof(data) / sizeof(data[0]);

    size_t n = 4;
    Tuple *result = repeat_tuple(&input, n);

    if (result != NULL) {
        for (size_t i = 0; i < result->size; ++i) {
            printf("%d ", result->elements[i]);
        }
        printf("\n");
        free_tuple(result);
    }

    return 0;
}