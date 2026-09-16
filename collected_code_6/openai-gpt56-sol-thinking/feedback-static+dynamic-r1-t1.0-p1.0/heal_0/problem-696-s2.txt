#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *values;
    size_t length;
} IntList;

typedef struct {
    const IntList *lists;
    size_t length;
} ListOfLists;

typedef struct {
    int first;
    int second;
} IntPair;

typedef struct {
    IntPair *pairs;
    size_t length;
} PairList;

typedef struct {
    PairList *lists;
    size_t length;
} ZippedLists;

typedef enum {
    ZIP_OK,
    ZIP_INVALID_ARGUMENT,
    ZIP_OUT_OF_MEMORY
} ZipStatus;

static size_t minimum_size(size_t first, size_t second)
{
    return first < second ? first : second;
}

static void *allocate_array(size_t count, size_t element_size)
{
    if (count == 0) {
        return NULL;
    }

    if (element_size > SIZE_MAX / count) {
        return NULL;
    }

    return calloc(count, element_size);
}

static bool is_valid_list_of_lists(const ListOfLists *list)
{
    size_t i;

    if (list == NULL) {
        return false;
    }

    if (list->length > 0 && list->lists == NULL) {
        return false;
    }

    for (i = 0; i < list->length; ++i) {
        if (list->lists[i].length > 0 && list->lists[i].values == NULL) {
            return false;
        }
    }

    return true;
}

void free_zipped_lists(ZippedLists *zipped)
{
    size_t i;

    if (zipped == NULL) {
        return;
    }

    for (i = 0; i < zipped->length; ++i) {
        free(zipped->lists[i].pairs);
    }

    free(zipped->lists);
    free(zipped);
}

ZippedLists *zip_lists_of_lists(const ListOfLists *first,
                                const ListOfLists *second,
                                ZipStatus *status)
{
    ZippedLists *result;
    size_t outer_length;
    size_t i;
    size_t j;

    if (status == NULL) {
        return NULL;
    }

    *status = ZIP_INVALID_ARGUMENT;

    if (!is_valid_list_of_lists(first) ||
        !is_valid_list_of_lists(second)) {
        return NULL;
    }

    result = calloc(1, sizeof(*result));
    if (result == NULL) {
        *status = ZIP_OUT_OF_MEMORY;
        return NULL;
    }

    outer_length = minimum_size(first->length, second->length);
    result->length = outer_length;

    if (outer_length > 0) {
        result->lists = allocate_array(outer_length, sizeof(*result->lists));
        if (result->lists == NULL) {
            free_zipped_lists(result);
            *status = ZIP_OUT_OF_MEMORY;
            return NULL;
        }
    }

    for (i = 0; i < outer_length; ++i) {
        size_t inner_length = minimum_size(first->lists[i].length,
                                           second->lists[i].length);

        result->lists[i].length = inner_length;

        if (inner_length > 0) {
            result->lists[i].pairs =
                allocate_array(inner_length, sizeof(*result->lists[i].pairs));

            if (result->lists[i].pairs == NULL) {
                free_zipped_lists(result);
                *status = ZIP_OUT_OF_MEMORY;
                return NULL;
            }
        }

        for (j = 0; j < inner_length; ++j) {
            result->lists[i].pairs[j].first = first->lists[i].values[j];
            result->lists[i].pairs[j].second = second->lists[i].values[j];
        }
    }

    *status = ZIP_OK;
    return result;
}

static bool print_zipped_lists(const ZippedLists *zipped)
{
    size_t i;
    size_t j;

    if (zipped == NULL) {
        return false;
    }

    if (puts("[") == EOF) {
        return false;
    }

    for (i = 0; i < zipped->length; ++i) {
        if (fputs("  [", stdout) == EOF) {
            return false;
        }

        for (j = 0; j < zipped->lists[i].length; ++j) {
            if (printf("(%d, %d)",
                       zipped->lists[i].pairs[j].first,
                       zipped->lists[i].pairs[j].second) < 0) {
                return false;
            }

            if (j + 1 < zipped->lists[i].length &&
                fputs(", ", stdout) == EOF) {
                return false;
            }
        }

        if (i + 1 < zipped->length) {
            if (puts("],") == EOF) {
                return false;
            }
        } else if (puts("]") == EOF) {
            return false;
        }
    }

    return puts("]") != EOF;
}

int main(void)
{
    static const int first_values_1[] = {1, 2, 3};
    static const int first_values_2[] = {4, 5};
    static const int first_values_3[] = {6};

    static const int second_values_1[] = {10, 20};
    static const int second_values_2[] = {30, 40, 50};
    static const int second_values_3[] = {60, 70};
    static const int second_values_4[] = {80};

    static const IntList first_lists[] = {
        {first_values_1, sizeof(first_values_1) / sizeof(first_values_1[0])},
        {first_values_2, sizeof(first_values_2) / sizeof(first_values_2[0])},
        {first_values_3, sizeof(first_values_3) / sizeof(first_values_3[0])}
    };

    static const IntList second_lists[] = {
        {second_values_1, sizeof(second_values_1) / sizeof(second_values_1[0])},
        {second_values_2, sizeof(second_values_2) / sizeof(second_values_2[0])},
        {second_values_3, sizeof(second_values_3) / sizeof(second_values_3[0])},
        {second_values_4, sizeof(second_values_4) / sizeof(second_values_4[0])}
    };

    const ListOfLists first = {
        first_lists,
        sizeof(first_lists) / sizeof(first_lists[0])
    };

    const ListOfLists second = {
        second_lists,
        sizeof(second_lists) / sizeof(second_lists[0])
    };

    ZippedLists *zipped;
    ZipStatus status;

    zipped = zip_lists_of_lists(&first, &second, &status);
    if (zipped == NULL) {
        if (status == ZIP_OUT_OF_MEMORY) {
            fputs("Unable to allocate memory.\n", stderr);
        } else {
            fputs("Invalid input.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (!print_zipped_lists(zipped) || fflush(stdout) == EOF) {
        free_zipped_lists(zipped);
        return EXIT_FAILURE;
    }

    free_zipped_lists(zipped);
    return EXIT_SUCCESS;
}