#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

static void destroy_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(tuples[i].elements);
        tuples[i].elements = NULL;
        tuples[i].length = 0;
    }

    free(tuples);
}

static bool remove_all_tuples_with_length(
    Tuple *tuples,
    size_t *tuple_count,
    size_t k)
{
    size_t write_index = 0;

    if (tuple_count == NULL || (*tuple_count != 0 && tuples == NULL)) {
        return false;
    }

    for (size_t read_index = 0; read_index < *tuple_count; ++read_index) {
        if (tuples[read_index].length == k) {
            free(tuples[read_index].elements);
            tuples[read_index].elements = NULL;
            tuples[read_index].length = 0;
            continue;
        }

        if (write_index != read_index) {
            tuples[write_index] = tuples[read_index];
            tuples[read_index].elements = NULL;
            tuples[read_index].length = 0;
        }

        ++write_index;
    }

    *tuple_count = write_index;
    return true;
}

static bool print_tuples(const Tuple *tuples, size_t count)
{
    if (printf("%zu\n", count) < 0) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("%zu", tuples[i].length) < 0) {
            return false;
        }

        for (size_t j = 0; j < tuples[i].length; ++j) {
            if (printf(" %d", tuples[i].elements[j]) < 0) {
                return false;
            }
        }

        if (putchar('\n') == EOF) {
            return false;
        }
    }

    return fflush(stdout) == 0;
}

int main(void)
{
    Tuple *tuples = NULL;
    size_t tuple_count = 0;
    size_t capacity = 0;
    size_t k = 0;

    if (scanf("%zu %zu", &tuple_count, &k) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (tuple_count > SIZE_MAX / sizeof(*tuples)) {
        fprintf(stderr, "Tuple count is too large\n");
        return EXIT_FAILURE;
    }

    capacity = tuple_count;

    if (capacity != 0) {
        tuples = calloc(capacity, sizeof(*tuples));
        if (tuples == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < capacity; ++i) {
        size_t length = 0;

        if (scanf("%zu", &length) != 1) {
            fprintf(stderr, "Invalid tuple length\n");
            destroy_tuples(tuples, capacity);
            return EXIT_FAILURE;
        }

        if (length > SIZE_MAX / sizeof(*tuples[i].elements)) {
            fprintf(stderr, "Tuple length is too large\n");
            destroy_tuples(tuples, capacity);
            return EXIT_FAILURE;
        }

        tuples[i].length = length;

        if (length != 0) {
            tuples[i].elements = malloc(length * sizeof(*tuples[i].elements));
            if (tuples[i].elements == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                destroy_tuples(tuples, capacity);
                return EXIT_FAILURE;
            }
        }

        for (size_t j = 0; j < length; ++j) {
            if (scanf("%d", &tuples[i].elements[j]) != 1) {
                fprintf(stderr, "Invalid tuple element\n");
                destroy_tuples(tuples, capacity);
                return EXIT_FAILURE;
            }
        }
    }

    if (!remove_all_tuples_with_length(tuples, &tuple_count, k)) {
        fprintf(stderr, "Failed to remove tuples\n");
        destroy_tuples(tuples, capacity);
        return EXIT_FAILURE;
    }

    if (!print_tuples(tuples, tuple_count)) {
        fprintf(stderr, "Output error\n");
        destroy_tuples(tuples, capacity);
        return EXIT_FAILURE;
    }

    destroy_tuples(tuples, capacity);
    return EXIT_SUCCESS;
}