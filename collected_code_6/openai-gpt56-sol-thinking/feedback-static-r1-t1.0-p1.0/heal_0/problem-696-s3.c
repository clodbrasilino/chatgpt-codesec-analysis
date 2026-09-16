#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    size_t length;
    const int *items;
} IntList;

typedef struct {
    size_t length;
    const IntList *lists;
} IntListOfLists;

typedef struct {
    int first;
    int second;
} IntPair;

typedef struct {
    size_t length;
    IntPair *items;
} PairList;

typedef struct {
    size_t length;
    PairList *lists;
} ZippedListOfLists;

typedef enum {
    ZIP_SUCCESS,
    ZIP_INVALID_ARGUMENT,
    ZIP_ALLOCATION_FAILURE
} ZipStatus;

static void initialize_zipped_lists(ZippedListOfLists *zipped)
{
    if (zipped != NULL) {
        zipped->length = 0;
        zipped->lists = NULL;
    }
}

static void free_zipped_lists(ZippedListOfLists *zipped)
{
    size_t i;

    if (zipped == NULL) {
        return;
    }

    for (i = 0; i < zipped->length; ++i) {
        free(zipped->lists[i].items);
        zipped->lists[i].items = NULL;
        zipped->lists[i].length = 0;
    }

    free(zipped->lists);
    initialize_zipped_lists(zipped);
}

static int validate_lists(const IntListOfLists *lists)
{
    size_t i;

    if (lists == NULL || (lists->length > 0 && lists->lists == NULL)) {
        return 0;
    }

    for (i = 0; i < lists->length; ++i) {
        if (lists->lists[i].length > 0 && lists->lists[i].items == NULL) {
            return 0;
        }
    }

    return 1;
}

static ZipStatus zip_lists_of_lists(
    const IntListOfLists *first,
    const IntListOfLists *second,
    ZippedListOfLists *result)
{
    ZippedListOfLists temporary;
    size_t outer_length;
    size_t i;
    size_t j;

    if (result == NULL || !validate_lists(first) || !validate_lists(second)) {
        return ZIP_INVALID_ARGUMENT;
    }

    if (result->length != 0 || result->lists != NULL) {
        return ZIP_INVALID_ARGUMENT;
    }

    initialize_zipped_lists(&temporary);
    outer_length = first->length < second->length
        ? first->length
        : second->length;

    if (outer_length == 0) {
        return ZIP_SUCCESS;
    }

    if (outer_length > SIZE_MAX / sizeof(*temporary.lists)) {
        return ZIP_ALLOCATION_FAILURE;
    }

    temporary.lists = calloc(outer_length, sizeof(*temporary.lists));
    if (temporary.lists == NULL) {
        return ZIP_ALLOCATION_FAILURE;
    }
    temporary.length = outer_length;

    for (i = 0; i < outer_length; ++i) {
        size_t inner_length = first->lists[i].length < second->lists[i].length
            ? first->lists[i].length
            : second->lists[i].length;

        temporary.lists[i].length = inner_length;

        if (inner_length == 0) {
            continue;
        }

        if (inner_length > SIZE_MAX / sizeof(*temporary.lists[i].items)) {
            free_zipped_lists(&temporary);
            return ZIP_ALLOCATION_FAILURE;
        }

        temporary.lists[i].items =
            malloc(inner_length * sizeof(*temporary.lists[i].items));

        if (temporary.lists[i].items == NULL) {
            free_zipped_lists(&temporary);
            return ZIP_ALLOCATION_FAILURE;
        }

        for (j = 0; j < inner_length; ++j) {
            temporary.lists[i].items[j].first = first->lists[i].items[j];
            temporary.lists[i].items[j].second = second->lists[i].items[j];
        }
    }

    *result = temporary;
    return ZIP_SUCCESS;
}

static int print_zipped_lists(const ZippedListOfLists *zipped)
{
    size_t i;
    size_t j;

    if (zipped == NULL || fputc('[', stdout) == EOF) {
        return 0;
    }

    for (i = 0; i < zipped->length; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            return 0;
        }

        if (fputc('[', stdout) == EOF) {
            return 0;
        }

        for (j = 0; j < zipped->lists[i].length; ++j) {
            if (j > 0 && fputs(", ", stdout) == EOF) {
                return 0;
            }

            if (printf(
                    "(%d, %d)",
                    zipped->lists[i].items[j].first,
                    zipped->lists[i].items[j].second) < 0) {
                return 0;
            }
        }

        if (fputc(']', stdout) == EOF) {
            return 0;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    const int first_row_1[] = {1, 2, 3};
    const int first_row_2[] = {4, 5};
    const int first_row_3[] = {6, 7, 8, 9};
    const int second_row_1[] = {10, 20, 30};
    const int second_row_2[] = {40, 50, 60};
    const int second_row_3[] = {70, 80};

    const IntList first_rows[] = {
        {3, first_row_1},
        {2, first_row_2},
        {4, first_row_3}
    };

    const IntList second_rows[] = {
        {3, second_row_1},
        {3, second_row_2},
        {2, second_row_3}
    };

    const IntListOfLists first = {
        sizeof(first_rows) / sizeof(first_rows[0]),
        first_rows
    };

    const IntListOfLists second = {
        sizeof(second_rows) / sizeof(second_rows[0]),
        second_rows
    };

    ZippedListOfLists result;
    ZipStatus status;

    initialize_zipped_lists(&result);
    status = zip_lists_of_lists(&first, &second, &result);

    if (status != ZIP_SUCCESS) {
        if (fprintf(stderr, "Failed to zip lists: error %d\n", status) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (!print_zipped_lists(&result)) {
        free_zipped_lists(&result);
        return EXIT_FAILURE;
    }

    free_zipped_lists(&result);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}