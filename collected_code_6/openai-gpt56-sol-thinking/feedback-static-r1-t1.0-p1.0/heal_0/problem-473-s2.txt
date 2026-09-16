#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

typedef enum {
    TUPLE_SUCCESS = 0,
    TUPLE_INVALID_ARGUMENT,
    TUPLE_ALLOCATION_FAILURE
} TupleStatus;

static bool tuple_is_valid(const Tuple *tuple)
{
    return tuple != NULL && (tuple->length == 0 || tuple->elements != NULL);
}

static bool tuple_equal_unordered(const Tuple *first, const Tuple *second)
{
    if (first->length != second->length) {
        return false;
    }

    for (size_t i = 0; i < first->length; ++i) {
        bool previously_counted = false;
        size_t first_count = 0;
        size_t second_count = 0;

        for (size_t j = 0; j < i; ++j) {
            if (first->elements[j] == first->elements[i]) {
                previously_counted = true;
                break;
            }
        }

        if (previously_counted) {
            continue;
        }

        for (size_t j = 0; j < first->length; ++j) {
            if (first->elements[j] == first->elements[i]) {
                ++first_count;
            }
            if (second->elements[j] == first->elements[i]) {
                ++second_count;
            }
        }

        if (first_count != second_count) {
            return false;
        }
    }

    return true;
}

static void free_tuple_list(Tuple *tuples, size_t count)
{
    if (tuples == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(tuples[i].elements);
    }

    free(tuples);
}

static TupleStatus clone_tuple(const Tuple *source, Tuple *destination)
{
    destination->elements = NULL;
    destination->length = 0;

    if (source->length == 0) {
        return TUPLE_SUCCESS;
    }

    if (source->length > SIZE_MAX / sizeof(*destination->elements)) {
        return TUPLE_ALLOCATION_FAILURE;
    }

    destination->elements = malloc(source->length * sizeof(*destination->elements));
    if (destination->elements == NULL) {
        return TUPLE_ALLOCATION_FAILURE;
    }

    for (size_t i = 0; i < source->length; ++i) {
        destination->elements[i] = source->elements[i];
    }

    destination->length = source->length;
    return TUPLE_SUCCESS;
}

static TupleStatus find_tuple_intersection(
    const Tuple *first,
    size_t first_count,
    const Tuple *second,
    size_t second_count,
    Tuple **intersection,
    size_t *intersection_count)
{
    bool *matched = NULL;
    Tuple *result = NULL;
    size_t result_count = 0;
    size_t capacity;

    if (intersection == NULL || intersection_count == NULL) {
        return TUPLE_INVALID_ARGUMENT;
    }

    *intersection = NULL;
    *intersection_count = 0;

    if ((first_count > 0 && first == NULL) ||
        (second_count > 0 && second == NULL)) {
        return TUPLE_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < first_count; ++i) {
        if (!tuple_is_valid(&first[i])) {
            return TUPLE_INVALID_ARGUMENT;
        }
    }

    for (size_t i = 0; i < second_count; ++i) {
        if (!tuple_is_valid(&second[i])) {
            return TUPLE_INVALID_ARGUMENT;
        }
    }

    capacity = first_count < second_count ? first_count : second_count;
    if (capacity == 0) {
        return TUPLE_SUCCESS;
    }

    if (capacity > SIZE_MAX / sizeof(*result)) {
        return TUPLE_ALLOCATION_FAILURE;
    }

    result = calloc(capacity, sizeof(*result));
    if (result == NULL) {
        return TUPLE_ALLOCATION_FAILURE;
    }

    matched = calloc(second_count, sizeof(*matched));
    if (matched == NULL) {
        free(result);
        return TUPLE_ALLOCATION_FAILURE;
    }

    for (size_t i = 0; i < first_count; ++i) {
        for (size_t j = 0; j < second_count; ++j) {
            if (!matched[j] && tuple_equal_unordered(&first[i], &second[j])) {
                TupleStatus status = clone_tuple(&first[i], &result[result_count]);

                if (status != TUPLE_SUCCESS) {
                    free(matched);
                    free_tuple_list(result, result_count);
                    return status;
                }

                matched[j] = true;
                ++result_count;
                break;
            }
        }
    }

    free(matched);

    if (result_count == 0) {
        free(result);
        return TUPLE_SUCCESS;
    }

    *intersection = result;
    *intersection_count = result_count;
    return TUPLE_SUCCESS;
}

static bool print_tuple_list(const Tuple *tuples, size_t count)
{
    if (printf("[") < 0) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("(") < 0) {
            return false;
        }

        for (size_t j = 0; j < tuples[i].length; ++j) {
            if (printf("%d%s", tuples[i].elements[j],
                       j + 1 < tuples[i].length ? ", " : "") < 0) {
                return false;
            }
        }

        if (printf(")%s", i + 1 < count ? ", " : "") < 0) {
            return false;
        }
    }

    return printf("]\n") >= 0;
}

int main(void)
{
    int first_values_1[] = {3, 4};
    int first_values_2[] = {5, 6};
    int first_values_3[] = {9, 10};
    int first_values_4[] = {4, 5};

    int second_values_1[] = {5, 4};
    int second_values_2[] = {4, 3};
    int second_values_3[] = {6, 5};
    int second_values_4[] = {9, 11};

    Tuple first[] = {
        {first_values_1, 2},
        {first_values_2, 2},
        {first_values_3, 2},
        {first_values_4, 2}
    };

    Tuple second[] = {
        {second_values_1, 2},
        {second_values_2, 2},
        {second_values_3, 2},
        {second_values_4, 2}
    };

    Tuple *intersection = NULL;
    size_t intersection_count = 0;
    TupleStatus status = find_tuple_intersection(
        first,
        sizeof(first) / sizeof(first[0]),
        second,
        sizeof(second) / sizeof(second[0]),
        &intersection,
        &intersection_count
    );

    if (status != TUPLE_SUCCESS) {
        fprintf(stderr, "Unable to find tuple intersection\n");
        return EXIT_FAILURE;
    }

    if (!print_tuple_list(intersection, intersection_count)) {
        free_tuple_list(intersection, intersection_count);
        return EXIT_FAILURE;
    }

    free_tuple_list(intersection, intersection_count);
    return EXIT_SUCCESS;
}