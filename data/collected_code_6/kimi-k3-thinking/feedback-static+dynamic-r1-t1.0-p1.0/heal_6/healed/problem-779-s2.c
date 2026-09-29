#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    const int *data;
    size_t length;
} IntList;

static int lists_equal(const IntList *first, const IntList *second)
{
    if (first == NULL || second == NULL) {
        return 0;
    }
    if (first->length != second->length) {
        return 0;
    }
    if (first->length == 0) {
        return 1;
    }
    if (first->data == NULL || second->data == NULL) {
        return first->data == second->data;
    }
    if (first->length > SIZE_MAX / sizeof(*first->data)) {
        return 0;
    }
    return memcmp(first->data, second->data, first->length * sizeof(*first->data)) == 0;
}

size_t count_unique_lists(const IntList *lists, size_t count)
{
    size_t unique_count = 0;
    size_t i;
    size_t j;

    if (lists == NULL && count > 0) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        int duplicate = 0;
        for (j = 0; j < i; ++j) {
            if (lists_equal(&lists[i], &lists[j])) {
                duplicate = 1;
                break;
            }
        }
        if (!duplicate) {
            ++unique_count;
        }
    }

    return unique_count;
}

static void free_storage(int **storage, size_t count)
{
    size_t k;

    if (storage == NULL) {
        return;
    }
    for (k = 0; k < count; ++k) {
        free(storage[k]);
        storage[k] = NULL;
    }
}

static int copy_int_list(int *destination, size_t destination_capacity, const int *source, size_t element_count)
{
    size_t copy_size;
    size_t n;

    if (element_count > 0 && (destination == NULL || source == NULL)) {
        return -1;
    }
    if (element_count > SIZE_MAX / sizeof(*source)) {
        return -1;
    }
    copy_size = element_count * sizeof(*source);
    if (destination_capacity < copy_size) {
        return -1;
    }
    for (n = 0; n < element_count; ++n) {
        destination[n] = source[n];
    }
    return 0;
}

int main(void)
{
    enum { LIST_COUNT = 5, MAX_LENGTH = 3 };
    const size_t lengths[LIST_COUNT] = {3, 2, 3, 3, 2};
    const int values[LIST_COUNT][MAX_LENGTH] = {
        {1, 2, 3},
        {4, 5, 0},
        {1, 2, 3},
        {4, 5, 6},
        {4, 5, 0}
    };
    IntList lists[LIST_COUNT];
    int *storage[LIST_COUNT];
    size_t i;
    size_t unique;

    for (i = 0; i < LIST_COUNT; ++i) {
        storage[i] = NULL;
        lists[i].data = NULL;
        lists[i].length = 0;
    }

    for (i = 0; i < LIST_COUNT; ++i) {
        size_t copy_size;
        size_t capacity;

        if (lengths[i] > MAX_LENGTH) {
            free_storage(storage, LIST_COUNT);
            fprintf(stderr, "error: list length exceeds source buffer capacity\n");
            return EXIT_FAILURE;
        }
        if (lengths[i] > SIZE_MAX / sizeof(*storage[i])) {
            free_storage(storage, LIST_COUNT);
            fprintf(stderr, "error: list length causes size computation overflow\n");
            return EXIT_FAILURE;
        }
        copy_size = lengths[i] * sizeof(*storage[i]);
        if (copy_size > sizeof(values[i])) {
            free_storage(storage, LIST_COUNT);
            fprintf(stderr, "error: copy size exceeds source buffer capacity\n");
            return EXIT_FAILURE;
        }
        capacity = copy_size > 0 ? copy_size : 1;
        storage[i] = malloc(capacity);
        if (storage[i] == NULL) {
            free_storage(storage, LIST_COUNT);
            fprintf(stderr, "error: memory allocation failed\n");
            return EXIT_FAILURE;
        }
        if (copy_int_list(storage[i], capacity, values[i], lengths[i]) != 0) {
            free_storage(storage, LIST_COUNT);
            fprintf(stderr, "error: failed to copy list data safely\n");
            return EXIT_FAILURE;
        }
        lists[i].data = storage[i];
        lists[i].length = lengths[i];
    }

    unique = count_unique_lists(lists, LIST_COUNT);

    if (printf("Number of unique lists: %zu\n", unique) < 0) {
        free_storage(storage, LIST_COUNT);
        fprintf(stderr, "error: failed to write output\n");
        return EXIT_FAILURE;
    }

    free_storage(storage, LIST_COUNT);

    return EXIT_SUCCESS;
}