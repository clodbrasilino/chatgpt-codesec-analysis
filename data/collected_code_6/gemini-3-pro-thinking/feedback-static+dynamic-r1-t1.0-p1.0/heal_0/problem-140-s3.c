#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare_ints(const void *a, const void *b) {
    int int_a = *((const int *)a);
    int int_b = *((const int *)b);
    if (int_a < int_b) {
        return -1;
    }
    if (int_a > int_b) {
        return 1;
    }
    return 0;
}

int* extract_single_elements(const Tuple *tuples, size_t num_tuples, size_t *out_size) {
    if (!tuples || !out_size || num_tuples == 0) {
        if (out_size) {
            *out_size = 0;
        }
        return NULL;
    }

    size_t total_elements = num_tuples * 2;
    int *all_elements = (int *)malloc(total_elements * sizeof(int));
    if (!all_elements) {
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < num_tuples; ++i) {
        all_elements[i * 2] = tuples[i].first;
        all_elements[i * 2 + 1] = tuples[i].second;
    }

    qsort(all_elements, total_elements, sizeof(int), compare_ints);

    int *result = (int *)malloc(total_elements * sizeof(int));
    if (!result) {
        free(all_elements);
        *out_size = 0;
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < total_elements; ++i) {
        int is_single = 1;
        if (i > 0 && all_elements[i] == all_elements[i - 1]) {
            is_single = 0;
        }
        if (i < total_elements - 1 && all_elements[i] == all_elements[i + 1]) {
            is_single = 0;
        }
        if (is_single) {
            result[count++] = all_elements[i];
        }
    }

    free(all_elements);

    if (count == 0) {
        free(result);
        *out_size = 0;
        return NULL;
    }

    int *shrunk_result = (int *)realloc(result, count * sizeof(int));
    if (!shrunk_result) {
        *out_size = count;
        return result;
    }

    *out_size = count;
    return shrunk_result;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2},
        {2, 3},
        {4, 5},
        {1, 6}
    };
    
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    size_t out_size = 0;

    int *singles = extract_single_elements(tuples, num_tuples, &out_size);

    for (size_t i = 0; i < out_size; ++i) {
        printf("%d\n", singles[i]);
    }

    if (singles) {
        free(singles);
    }

    return 0;
}