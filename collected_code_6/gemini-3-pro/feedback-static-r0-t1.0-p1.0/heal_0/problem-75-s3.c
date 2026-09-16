#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* elements;
    size_t size;
} Tuple;

bool is_divisible_by_k(const Tuple* tuple, int k) {
    if (tuple == NULL || tuple->elements == NULL || k == 0) {
        return false;
    }
    
    for (size_t i = 0; i < tuple->size; ++i) {
        if (tuple->elements[i] % k != 0) {
            return false;
        }
    }
    return true;
}

Tuple** find_tuples_divisible_by_k(Tuple** tuples, size_t num_tuples, int k, size_t* out_count) {
    if (tuples == NULL || out_count == NULL || k == 0) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    Tuple** result = malloc(num_tuples * sizeof(Tuple*));
    if (result == NULL) {
        *out_count = 0;
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < num_tuples; ++i) {
        if (tuples[i] != NULL && is_divisible_by_k(tuples[i], k)) {
            result[count++] = tuples[i];
        }
    }

    *out_count = count;
    
    if (count == 0) {
        free(result);
        return NULL;
    }

    Tuple** resized_result = realloc(result, count * sizeof(Tuple*));
    if (resized_result != NULL) {
        return resized_result;
    }
    
    return result;
}

int main(void) {
    int elems1[] = {4, 8, 12};
    Tuple t1 = {elems1, 3};

    int elems2[] = {4, 9, 12};
    Tuple t2 = {elems2, 3};

    int elems3[] = {16, 20};
    Tuple t3 = {elems3, 2};

    Tuple* tuples[] = {&t1, &t2, &t3};
    size_t num_tuples = 3;
    int k = 4;
    size_t out_count = 0;

    Tuple** result = find_tuples_divisible_by_k(tuples, num_tuples, k, &out_count);

    if (result != NULL) {
        for (size_t i = 0; i < out_count; ++i) {
            for (size_t j = 0; j < result[i]->size; ++j) {
                printf("%d ", result[i]->elements[j]);
            }
            printf("\n");
        }
        free(result);
    }

    return 0;
}