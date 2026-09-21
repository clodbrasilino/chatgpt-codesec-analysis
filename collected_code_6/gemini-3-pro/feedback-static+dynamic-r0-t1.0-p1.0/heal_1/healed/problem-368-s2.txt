#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

Tuple* repeat_tuple(const Tuple *input, size_t n) {
    if (input == NULL || input->data == NULL) {
        return NULL;
    }

    Tuple *result = (Tuple *)malloc(sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    if (n == 0 || input->size == 0) {
        result->data = NULL;
        result->size = 0;
        return result;
    }

    if (input->size > SIZE_MAX / n) {
        free(result);
        return NULL;
    }

    result->size = input->size * n;
    
    if (result->size > SIZE_MAX / sizeof(int)) {
        free(result);
        return NULL;
    }

    result->data = (int *)malloc(result->size * sizeof(int));
    if (result->data == NULL) {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < n; ++i) {
        memcpy(result->data + (i * input->size), input->data, input->size * sizeof(int));
    }

    return result;
}

void print_tuple(const Tuple *t) {
    if (t == NULL) {
        printf("NULL\n");
        return;
    }
    printf("(");
    for (size_t i = 0; i < t->size; ++i) {
        printf("%d", t->data[i]);
        if (i < t->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    int initial_data[] = {1, 2, 3};
    Tuple input_tuple = {initial_data, 3};

    Tuple *repeated = repeat_tuple(&input_tuple, 4);

    if (repeated != NULL) {
        print_tuple(repeated);
        free(repeated->data);
        free(repeated);
    }

    return 0;
}