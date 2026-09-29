#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t length;
} IntList;

typedef struct {
    IntList *lists;
    size_t count;
} IntListCollection;

typedef enum {
    LIST_STATUS_OK = 0,
    LIST_STATUS_INVALID_ARGUMENT,
    LIST_STATUS_ALLOCATION_FAILURE,
    LIST_STATUS_SIZE_OVERFLOW
} ListStatus;

static void int_list_collection_init(IntListCollection *collection)
{
    if (collection != NULL) {
        collection->lists = NULL;
        collection->count = 0;
    }
}

static void int_list_collection_destroy(IntListCollection *collection)
{
    size_t i;

    if (collection == NULL) {
        return;
    }

    for (i = 0; i < collection->count; ++i) {
        free(collection->lists[i].values);
    }

    free(collection->lists);
    collection->lists = NULL;
    collection->count = 0;
}

static ListStatus find_minimum_length_lists(
    const IntList *lists,
    size_t count,
    IntListCollection *output)
{
    IntListCollection result;
    size_t minimum_length;
    size_t matching_count;
    size_t result_index;
    size_t i;

    if (output == NULL || (count != 0 && lists == NULL)) {
        return LIST_STATUS_INVALID_ARGUMENT;
    }

    int_list_collection_init(&result);

    if (count == 0) {
        int_list_collection_destroy(output);
        *output = result;
        return LIST_STATUS_OK;
    }

    minimum_length = lists[0].length;

    for (i = 0; i < count; ++i) {
        if (lists[i].length != 0 && lists[i].values == NULL) {
            return LIST_STATUS_INVALID_ARGUMENT;
        }

        if (lists[i].length < minimum_length) {
            minimum_length = lists[i].length;
        }
    }

    matching_count = 0;

    for (i = 0; i < count; ++i) {
        if (lists[i].length == minimum_length) {
            ++matching_count;
        }
    }

    if (matching_count > SIZE_MAX / sizeof(*result.lists)) {
        return LIST_STATUS_SIZE_OVERFLOW;
    }

    result.lists = calloc(matching_count, sizeof(*result.lists));
    if (result.lists == NULL) {
        return LIST_STATUS_ALLOCATION_FAILURE;
    }

    result.count = matching_count;
    result_index = 0;

    for (i = 0; i < count; ++i) {
        if (lists[i].length == minimum_length) {
            result.lists[result_index].length = minimum_length;

            if (minimum_length != 0) {
                size_t byte_count;
                size_t j;

                if (minimum_length >
                    SIZE_MAX / sizeof(*result.lists[result_index].values)) {
                    int_list_collection_destroy(&result);
                    return LIST_STATUS_SIZE_OVERFLOW;
                }

                byte_count =
                    minimum_length *
                    sizeof(*result.lists[result_index].values);

                result.lists[result_index].values = malloc(byte_count);
                if (result.lists[result_index].values == NULL) {
                    int_list_collection_destroy(&result);
                    return LIST_STATUS_ALLOCATION_FAILURE;
                }

                for (j = 0; j < minimum_length; ++j) {
                    result.lists[result_index].values[j] =
                        lists[i].values[j];
                }
            }

            ++result_index;
        }
    }

    int_list_collection_destroy(output);
    *output = result;

    return LIST_STATUS_OK;
}

static void print_list(const IntList *list)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    putchar('[');

    for (i = 0; i < list->length; ++i) {
        if (i != 0) {
            printf(", ");
        }

        printf("%d", list->values[i]);
    }

    putchar(']');
}

int main(void)
{
    int values1[] = {1, 2, 3};
    int values2[] = {4, 5};
    int values3[] = {6, 7, 8, 9};
    int values4[] = {10, 11};
    IntList input[] = {
        {values1, sizeof(values1) / sizeof(values1[0])},
        {values2, sizeof(values2) / sizeof(values2[0])},
        {values3, sizeof(values3) / sizeof(values3[0])},
        {values4, sizeof(values4) / sizeof(values4[0])}
    };
    IntListCollection result;
    ListStatus status;
    size_t i;

    int_list_collection_init(&result);

    status = find_minimum_length_lists(
        input,
        sizeof(input) / sizeof(input[0]),
        &result);

    if (status != LIST_STATUS_OK) {
        fprintf(
            stderr,
            "Unable to find minimum-length lists: %d\n",
            (int)status);
        int_list_collection_destroy(&result);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result.count; ++i) {
        print_list(&result.lists[i]);
        putchar('\n');
    }

    int_list_collection_destroy(&result);
    return EXIT_SUCCESS;
}