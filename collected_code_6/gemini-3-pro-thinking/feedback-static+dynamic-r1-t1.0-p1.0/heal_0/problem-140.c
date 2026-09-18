#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare_ints(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    if (int_a < int_b) {
        return -1;
    }
    if (int_a > int_b) {
        return 1;
    }
    return 0;
}

int *extract_single_elements(const Tuple *tuples, size_t num_tuples, size_t *out_count) {
    if (!tuples || !out_count) {
        if (out_count) {
            *out_count = 0;
        }
        return NULL;
    }

    if (num_tuples == 0) {
        *out_count = 0;
        return NULL;
    }

    size_t total_elements = num_tuples * 2;
    int *flat = (int *)malloc(total_elements * sizeof(int));
    if (!flat) {
        *out_count = 0;
        return NULL;
    }

    for (size_t i = 0; i < num_tuples; ++i) {
        flat[2 * i] = tuples[i].first;
        flat[2 * i + 1] = tuples[i].second;
    }

    qsort(flat, total_elements, sizeof(int), compare_ints);

    size_t unique_count = 0;
    for (size_t i = 0; i < total_elements; ) {
        size_t count = 1;
        while (i + count < total_elements && flat[i] == flat[i + count]) {
            count++;
        }
        if (count == 1) {
            flat[unique_count++] = flat[i];
        }
        i += count;
    }

    *out_count = unique_count;

    if (unique_count == 0) {
        free(flat);
        return NULL;
    }

    int *result = (int *)realloc(flat, unique_count * sizeof(int));
    if (!result) {
        return flat;
    }

    return result;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2},
        {2, 3},
        {1, 4},
        {5, 6},
        {6, 7}
    };
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    size_t out_count = 0;

    int *singles = extract_single_elements(tuples, num_tuples, &out_count);

    if (singles) {
        for (size_t i = 0; i < out_count; ++i) {
            printf("%d\n", singles[i]);
        }
        free(singles);
        singles = NULL;
    }

    return 0;
}