#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} IntList;

typedef struct {
    IntList *items;
    size_t count;
} ListOfLists;

static void free_list_of_lists(ListOfLists *lists)
{
    size_t i;

    if (lists == NULL) {
        return;
    }

    for (i = 0; i < lists->count; ++i) {
        free(lists->items[i].data);
    }

    free(lists->items);
    lists->items = NULL;
    lists->count = 0;
}

static int initialize_list_of_lists(
    ListOfLists *result,
    const int *const *sources,
    const size_t *lengths,
    size_t count)
{
    size_t i;

    if (result == NULL ||
        (count > 0 && (sources == NULL || lengths == NULL)) ||
        count > SIZE_MAX / sizeof(*result->items)) {
        return 0;
    }

    result->items = NULL;
    result->count = 0;

    if (count == 0) {
        return 1;
    }

    result->items = calloc(count, sizeof(*result->items));
    if (result->items == NULL) {
        return 0;
    }

    result->count = count;

    for (i = 0; i < count; ++i) {
        if (lengths[i] == 0) {
            continue;
        }

        if (sources[i] == NULL ||
            lengths[i] > SIZE_MAX / sizeof(*result->items[i].data)) {
            free_list_of_lists(result);
            return 0;
        }

        result->items[i].data =
            malloc(lengths[i] * sizeof(*result->items[i].data));

        if (result->items[i].data == NULL) {
            free_list_of_lists(result);
            return 0;
        }

        result->items[i].length = lengths[i];

        for (size_t j = 0; j < lengths[i]; ++j) {
            result->items[i].data[j] = sources[i][j];
        }
    }

    return 1;
}

static int lists_are_equal(const IntList *left, const IntList *right)
{
    size_t i;

    if (left->length != right->length) {
        return 0;
    }

    for (i = 0; i < left->length; ++i) {
        if (left->data[i] != right->data[i]) {
            return 0;
        }
    }

    return 1;
}

static int remove_duplicates(ListOfLists *lists)
{
    size_t read_index;
    size_t write_index = 0;

    if (lists == NULL || (lists->count > 0 && lists->items == NULL)) {
        return 0;
    }

    for (read_index = 0; read_index < lists->count; ++read_index) {
        if ((lists->items[read_index].length > 0 &&
             lists->items[read_index].data == NULL) ||
            lists->items[read_index].length >
                SIZE_MAX / sizeof(*lists->items[read_index].data)) {
            return 0;
        }
    }

    for (read_index = 0; read_index < lists->count; ++read_index) {
        size_t i;
        int duplicate = 0;

        for (i = 0; i < write_index; ++i) {
            if (lists_are_equal(&lists->items[read_index],
                                &lists->items[i])) {
                duplicate = 1;
                break;
            }
        }

        if (duplicate) {
            free(lists->items[read_index].data);
            lists->items[read_index].data = NULL;
            lists->items[read_index].length = 0;
            continue;
        }

        if (write_index != read_index) {
            lists->items[write_index] = lists->items[read_index];
            lists->items[read_index].data = NULL;
            lists->items[read_index].length = 0;
        }

        ++write_index;
    }

    lists->count = write_index;
    return 1;
}

static int print_list_of_lists(const ListOfLists *lists)
{
    size_t i;

    if (lists == NULL || (lists->count > 0 && lists->items == NULL)) {
        return 0;
    }

    if (fputc('[', stdout) == EOF) {
        return 0;
    }

    for (i = 0; i < lists->count; ++i) {
        size_t j;

        if (i > 0 && fputs(", ", stdout) == EOF) {
            return 0;
        }

        if (fputc('[', stdout) == EOF) {
            return 0;
        }

        for (j = 0; j < lists->items[i].length; ++j) {
            if (j > 0 && fputs(", ", stdout) == EOF) {
                return 0;
            }

            if (printf("%d", lists->items[i].data[j]) < 0) {
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
    static const int first[] = {1, 2, 3};
    static const int second[] = {4, 5};
    static const int third[] = {1, 2, 3};
    static const int sixth[] = {6, 7};
    static const int seventh[] = {4, 5};
    static const int eighth[] = {6, 7};

    const int *sources[] = {
        first,
        second,
        third,
        NULL,
        NULL,
        sixth,
        seventh,
        eighth
    };

    const size_t lengths[] = {
        sizeof(first) / sizeof(first[0]),
        sizeof(second) / sizeof(second[0]),
        sizeof(third) / sizeof(third[0]),
        0,
        0,
        sizeof(sixth) / sizeof(sixth[0]),
        sizeof(seventh) / sizeof(seventh[0]),
        sizeof(eighth) / sizeof(eighth[0])
    };

    ListOfLists lists;

    if (!initialize_list_of_lists(
            &lists,
            sources,
            lengths,
            sizeof(lengths) / sizeof(lengths[0]))) {
        fputs("Failed to initialize the list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!remove_duplicates(&lists)) {
        fputs("Failed to remove duplicates.\n", stderr);
        free_list_of_lists(&lists);
        return EXIT_FAILURE;
    }

    if (!print_list_of_lists(&lists)) {
        free_list_of_lists(&lists);
        return EXIT_FAILURE;
    }

    free_list_of_lists(&lists);
    return EXIT_SUCCESS;
}