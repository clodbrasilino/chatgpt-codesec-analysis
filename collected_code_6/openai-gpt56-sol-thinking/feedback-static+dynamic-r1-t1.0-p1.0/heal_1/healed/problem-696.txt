#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    const int *data;
    size_t length;
} IntListView;

typedef struct {
    const IntListView *lists;
    size_t length;
} ListOfListsView;

typedef struct {
    int *data;
    size_t length;
} IntList;

typedef struct {
    IntList first;
    IntList second;
} ListPair;

typedef struct {
    ListPair *pairs;
    size_t length;
} ZippedList;

static void zipped_list_init(ZippedList *list)
{
    if (list != NULL) {
        list->pairs = NULL;
        list->length = 0;
    }
}

static void int_list_destroy(IntList *list)
{
    if (list != NULL) {
        free(list->data);
        list->data = NULL;
        list->length = 0;
    }
}

static void zipped_list_destroy(ZippedList *list)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < list->length; ++i) {
        int_list_destroy(&list->pairs[i].first);
        int_list_destroy(&list->pairs[i].second);
    }

    free(list->pairs);
    list->pairs = NULL;
    list->length = 0;
}

static bool int_list_copy(IntList *destination, const IntListView *source)
{
    int *data;
    size_t i;

    if (destination == NULL || source == NULL) {
        return false;
    }

    destination->data = NULL;
    destination->length = 0;

    if (source->length == 0) {
        return true;
    }

    if (source->data == NULL ||
        source->length > SIZE_MAX / sizeof(*data)) {
        return false;
    }

    data = malloc(source->length * sizeof(*data));
    if (data == NULL) {
        return false;
    }

    for (i = 0; i < source->length; ++i) {
        data[i] = source->data[i];
    }

    destination->data = data;
    destination->length = source->length;
    return true;
}

static bool zip_lists_of_lists(const ListOfListsView *first,
                               const ListOfListsView *second,
                               ZippedList *result)
{
    ZippedList temporary;
    size_t count;
    size_t i;

    if (first == NULL || second == NULL || result == NULL) {
        return false;
    }

    if (result->pairs != NULL || result->length != 0) {
        return false;
    }

    if ((first->length != 0 && first->lists == NULL) ||
        (second->length != 0 && second->lists == NULL)) {
        return false;
    }

    zipped_list_init(&temporary);

    count = first->length < second->length
                ? first->length
                : second->length;

    if (count == 0) {
        *result = temporary;
        return true;
    }

    if (count > SIZE_MAX / sizeof(*temporary.pairs)) {
        return false;
    }

    temporary.pairs = calloc(count, sizeof(*temporary.pairs));
    if (temporary.pairs == NULL) {
        return false;
    }

    temporary.length = count;

    for (i = 0; i < count; ++i) {
        if (!int_list_copy(&temporary.pairs[i].first, &first->lists[i]) ||
            !int_list_copy(&temporary.pairs[i].second, &second->lists[i])) {
            zipped_list_destroy(&temporary);
            return false;
        }
    }

    *result = temporary;
    return true;
}

static bool print_int_list(const IntList *list)
{
    size_t i;

    if (list == NULL ||
        (list->length != 0 && list->data == NULL)) {
        return false;
    }

    if (putchar('[') == EOF) {
        return false;
    }

    for (i = 0; i < list->length; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (printf("%d", list->data[i]) < 0) {
            return false;
        }
    }

    return putchar(']') != EOF;
}

static bool print_zipped_list(const ZippedList *list)
{
    size_t i;

    if (list == NULL ||
        (list->length != 0 && list->pairs == NULL)) {
        return false;
    }

    if (putchar('[') == EOF) {
        return false;
    }

    for (i = 0; i < list->length; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (putchar('[') == EOF ||
            !print_int_list(&list->pairs[i].first) ||
            fputs(", ", stdout) == EOF ||
            !print_int_list(&list->pairs[i].second) ||
            putchar(']') == EOF) {
            return false;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    const int first_row_1[] = {1, 2, 3};
    const int first_row_2[] = {4, 5};
    const int first_row_3[] = {6};
    const int second_row_1[] = {10, 20};
    const int second_row_2[] = {30, 40, 50};
    const int second_row_3[] = {60, 70};

    const IntListView first_lists[] = {
        {first_row_1, sizeof(first_row_1) / sizeof(first_row_1[0])},
        {first_row_2, sizeof(first_row_2) / sizeof(first_row_2[0])},
        {first_row_3, sizeof(first_row_3) / sizeof(first_row_3[0])}
    };

    const IntListView second_lists[] = {
        {second_row_1, sizeof(second_row_1) / sizeof(second_row_1[0])},
        {second_row_2, sizeof(second_row_2) / sizeof(second_row_2[0])},
        {second_row_3, sizeof(second_row_3) / sizeof(second_row_3[0])}
    };

    const ListOfListsView first = {
        first_lists,
        sizeof(first_lists) / sizeof(first_lists[0])
    };

    const ListOfListsView second = {
        second_lists,
        sizeof(second_lists) / sizeof(second_lists[0])
    };

    ZippedList result;

    zipped_list_init(&result);

    if (!zip_lists_of_lists(&first, &second, &result)) {
        fputs("Unable to zip the lists.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!print_zipped_list(&result)) {
        zipped_list_destroy(&result);
        fputs("Unable to print the result.\n", stderr);
        return EXIT_FAILURE;
    }

    zipped_list_destroy(&result);
    return EXIT_SUCCESS;
}