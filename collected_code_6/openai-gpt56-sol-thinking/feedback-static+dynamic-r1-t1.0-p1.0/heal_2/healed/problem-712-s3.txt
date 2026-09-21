#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t length;
} IntList;

typedef struct {
    IntList *items;
    size_t length;
} ListOfLists;

static void list_of_lists_destroy(ListOfLists *list)
{
    if (list == NULL) {
        return;
    }

    if (list->items != NULL) {
        for (size_t i = 0; i < list->length; ++i) {
            free(list->items[i].items);
        }
    }

    free(list->items);
    list->items = NULL;
    list->length = 0;
}

static bool list_of_lists_init(
    ListOfLists *list,
    const int *const *sources,
    const size_t *lengths,
    size_t count)
{
    if (list == NULL) {
        return false;
    }

    list->items = NULL;
    list->length = 0;

    if (count > 0 && (sources == NULL || lengths == NULL)) {
        return false;
    }

    if (count == 0) {
        return true;
    }

    if (count > SIZE_MAX / sizeof(*list->items)) {
        return false;
    }

    list->items = calloc(count, sizeof(*list->items));
    if (list->items == NULL) {
        return false;
    }

    list->length = count;

    for (size_t i = 0; i < count; ++i) {
        if (lengths[i] == 0) {
            continue;
        }

        if (sources[i] == NULL ||
            lengths[i] > SIZE_MAX / sizeof(*list->items[i].items)) {
            list_of_lists_destroy(list);
            return false;
        }

        list->items[i].items =
            malloc(lengths[i] * sizeof(*list->items[i].items));

        if (list->items[i].items == NULL) {
            list_of_lists_destroy(list);
            return false;
        }

        for (size_t j = 0; j < lengths[i]; ++j) {
            list->items[i].items[j] = sources[i][j];
        }

        list->items[i].length = lengths[i];
    }

    return true;
}

static bool int_lists_equal(const IntList *left, const IntList *right)
{
    if (left->length != right->length) {
        return false;
    }

    for (size_t i = 0; i < left->length; ++i) {
        if (left->items[i] != right->items[i]) {
            return false;
        }
    }

    return true;
}

bool remove_duplicates(ListOfLists *list)
{
    if (list == NULL ||
        (list->length > 0 && list->items == NULL) ||
        list->length > SIZE_MAX / sizeof(*list->items)) {
        return false;
    }

    for (size_t read_index = 0;
         read_index < list->length;
         ++read_index) {
        if ((list->items[read_index].length > 0 &&
             list->items[read_index].items == NULL) ||
            list->items[read_index].length >
                SIZE_MAX / sizeof(*list->items[read_index].items)) {
            return false;
        }

        for (size_t other_index = 0;
             other_index < read_index;
             ++other_index) {
            if (list->items[read_index].items != NULL &&
                list->items[read_index].items ==
                    list->items[other_index].items) {
                return false;
            }
        }
    }

    size_t write_index = 0;

    for (size_t read_index = 0;
         read_index < list->length;
         ++read_index) {
        bool duplicate = false;

        for (size_t compare_index = 0;
             compare_index < write_index;
             ++compare_index) {
            if (int_lists_equal(
                    &list->items[read_index],
                    &list->items[compare_index])) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            free(list->items[read_index].items);
            list->items[read_index].items = NULL;
            list->items[read_index].length = 0;
            continue;
        }

        if (write_index != read_index) {
            list->items[write_index] = list->items[read_index];
            list->items[read_index].items = NULL;
            list->items[read_index].length = 0;
        }

        ++write_index;
    }

    list->length = write_index;
    return true;
}

static bool print_list_of_lists(const ListOfLists *list)
{
    if (list == NULL ||
        (list->length > 0 && list->items == NULL) ||
        list->length > SIZE_MAX / sizeof(*list->items)) {
        return false;
    }

    if (fputs("[\n", stdout) == EOF) {
        return false;
    }

    for (size_t i = 0; i < list->length; ++i) {
        if ((list->items[i].length > 0 &&
             list->items[i].items == NULL) ||
            list->items[i].length >
                SIZE_MAX / sizeof(*list->items[i].items)) {
            return false;
        }

        if (fputs("  [", stdout) == EOF) {
            return false;
        }

        for (size_t j = 0; j < list->items[i].length; ++j) {
            if (j > 0 && fputs(", ", stdout) == EOF) {
                return false;
            }

            if (printf("%d", list->items[i].items[j]) < 0) {
                return false;
            }
        }

        if (fputc(']', stdout) == EOF) {
            return false;
        }

        if (i + 1 < list->length && fputc(',', stdout) == EOF) {
            return false;
        }

        if (fputc('\n', stdout) == EOF) {
            return false;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    static const int first[] = {1, 2, 3};
    static const int second[] = {4, 5};
    static const int third[] = {1, 2, 3};
    static const int sixth[] = {4, 5};
    static const int seventh[] = {7};

    const int *const sources[] = {
        first,
        second,
        third,
        NULL,
        NULL,
        sixth,
        seventh
    };

    const size_t lengths[] = {
        3,
        2,
        3,
        0,
        0,
        2,
        1
    };

    ListOfLists list;

    if (!list_of_lists_init(
            &list,
            sources,
            lengths,
            sizeof(lengths) / sizeof(lengths[0]))) {
        fputs("Failed to create the list of lists.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!remove_duplicates(&list)) {
        fputs("Failed to remove duplicates.\n", stderr);
        list_of_lists_destroy(&list);
        return EXIT_FAILURE;
    }

    if (!print_list_of_lists(&list)) {
        fputs("Failed to print the list of lists.\n", stderr);
        list_of_lists_destroy(&list);
        return EXIT_FAILURE;
    }

    list_of_lists_destroy(&list);
    return EXIT_SUCCESS;
}