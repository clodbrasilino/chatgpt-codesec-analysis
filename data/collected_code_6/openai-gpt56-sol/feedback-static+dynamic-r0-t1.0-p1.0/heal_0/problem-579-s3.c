#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

static int contains(const Tuple *tuple, int value)
{
    if (tuple == NULL || (tuple->size > 0U && tuple->data == NULL)) {
        return 0;
    }

    for (size_t i = 0; i < tuple->size; ++i) {
        if (tuple->data[i] == value) {
            return 1;
        }
    }

    return 0;
}

static int append_unique(Tuple *tuple, int value, size_t capacity)
{
    if (tuple == NULL || tuple->data == NULL || tuple->size >= capacity) {
        return 0;
    }

    if (!contains(tuple, value)) {
        tuple->data[tuple->size++] = value;
    }

    return 1;
}

static int find_dissimilar(const Tuple *first, const Tuple *second, Tuple *result)
{
    size_t capacity;

    if (first == NULL || second == NULL || result == NULL ||
        (first->size > 0U && first->data == NULL) ||
        (second->size > 0U && second->data == NULL)) {
        return 0;
    }

    result->data = NULL;
    result->size = 0U;

    if (first->size > SIZE_MAX - second->size) {
        return 0;
    }

    capacity = first->size + second->size;
    if (capacity == 0U) {
        return 1;
    }

    if (capacity > SIZE_MAX / sizeof(*result->data)) {
        return 0;
    }

    result->data = malloc(capacity * sizeof(*result->data));
    if (result->data == NULL) {
        return 0;
    }

    for (size_t i = 0; i < first->size; ++i) {
        if (!contains(second, first->data[i]) &&
            !append_unique(result, first->data[i], capacity)) {
            free(result->data);
            result->data = NULL;
            result->size = 0U;
            return 0;
        }
    }

    for (size_t i = 0; i < second->size; ++i) {
        if (!contains(first, second->data[i]) &&
            !append_unique(result, second->data[i], capacity)) {
            free(result->data);
            result->data = NULL;
            result->size = 0U;
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    int first_data[] = {1, 2, 3, 4, 4};
    int second_data[] = {3, 4, 5, 6, 6};
    Tuple first = {first_data, sizeof(first_data) / sizeof(first_data[0])};
    Tuple second = {second_data, sizeof(second_data) / sizeof(second_data[0])};
    Tuple result = {NULL, 0U};

    if (!find_dissimilar(&first, &second, &result)) {
        fputs("Failed to find dissimilar elements.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("(");
    for (size_t i = 0; i < result.size; ++i) {
        printf("%s%d", i == 0U ? "" : ", ", result.data[i]);
    }
    printf(")\n");

    free(result.data);
    return EXIT_SUCCESS;
}