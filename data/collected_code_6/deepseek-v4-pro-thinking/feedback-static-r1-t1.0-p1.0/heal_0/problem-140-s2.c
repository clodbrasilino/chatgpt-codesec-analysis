#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

static int count_occurrences(const int *sorted_values, size_t count, int value) {
    const int *found = (const int *)bsearch(&value, sorted_values, count, sizeof(int), compare_ints);

    if (found == NULL) {
        return 0;
    }

    size_t index = (size_t)(found - sorted_values);
    int occurrences = 1;
    size_t i = index;

    while (i > 0 && sorted_values[i - 1] == value) {
        --i;
        ++occurrences;
    }

    i = index;

    while (i + 1 < count && sorted_values[i + 1] == value) {
        ++i;
        ++occurrences;
    }

    return occurrences;
}

int *extract_single_occurrences(const Tuple *tuples, int tuple_count, int *result_count) {
    if (result_count == NULL) {
        return NULL;
    }

    *result_count = -1;

    if (tuple_count < 0) {
        return NULL;
    }

    if (tuple_count == 0) {
        *result_count = 0;
        return NULL;
    }

    if (tuples == NULL) {
        return NULL;
    }

    size_t total_elements = (size_t)tuple_count * 2;

    if (total_elements / 2 != (size_t)tuple_count ||
        total_elements > (size_t)-1 / sizeof(int)) {
        return NULL;
    }

    int *all_elements = (int *)malloc(total_elements * sizeof(int));

    if (all_elements == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < (size_t)tuple_count; ++i) {
        all_elements[i * 2] = tuples[i].first;
        all_elements[i * 2 + 1] = tuples[i].second;
    }

    qsort(all_elements, total_elements, sizeof(int), compare_ints);

    int *result = (int *)malloc(total_elements * sizeof(int));

    if (result == NULL) {
        free(all_elements);
        return NULL;
    }

    int single_count = 0;

    for (int i = 0; i < tuple_count; ++i) {
        if (count_occurrences(all_elements, total_elements, tuples[i].first) == 1) {
            result[single_count++] = tuples[i].first;
        }

        if (count_occurrences(all_elements, total_elements, tuples[i].second) == 1) {
            result[single_count++] = tuples[i].second;
        }
    }

    free(all_elements);

    if (single_count == 0) {
        free(result);
        *result_count = 0;
        return NULL;
    }

    int *shrunk = (int *)realloc(result, (size_t)single_count * sizeof(int));

    if (shrunk != NULL) {
        result = shrunk;
    }

    *result_count = single_count;
    return result;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2},
        {2, 3},
        {4, 5}
    };

    int tuple_count = (int)(sizeof(tuples) / sizeof(tuples[0]));
    int single_count = 0;
    int *single_elements = extract_single_occurrences(tuples, tuple_count, &single_count);

    if (single_elements == NULL) {
        if (single_count == -1) {
            printf("Error: invalid input or memory allocation failure\n");
            return EXIT_FAILURE;
        }

        if (single_count == 0) {
            printf("No singly occurring elements\n");
            return EXIT_SUCCESS;
        }

        printf("Error: unknown failure\n");
        return EXIT_FAILURE;
    }

    printf("Singly occurring elements:");

    for (int i = 0; i < single_count; ++i) {
        printf(" %d", single_elements[i]);
    }

    printf("\n");

    free(single_elements);
    return EXIT_SUCCESS;
}