#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *values;
    size_t length;
} IntListView;

typedef struct {
    int *values;
    size_t length;
} IntList;

typedef enum {
    LIST_SUCCESS = 0,
    LIST_INVALID_ARGUMENT,
    LIST_ALLOCATION_FAILURE,
    LIST_SIZE_OVERFLOW
} ListStatus;

void free_int_lists(IntList *lists, size_t count)
{
    size_t i;

    if (lists == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(lists[i].values);
    }

    free(lists);
}

ListStatus find_max_length_lists(const IntListView *lists,
                                 size_t list_count,
                                 IntList **result,
                                 size_t *result_count,
                                 size_t *maximum_length)
{
    IntList *copies;
    size_t max_length = 0;
    size_t match_count = 0;
    size_t written = 0;
    size_t i;
    size_t j;

    if (result == NULL || result_count == NULL || maximum_length == NULL) {
        return LIST_INVALID_ARGUMENT;
    }

    *result = NULL;
    *result_count = 0;
    *maximum_length = 0;

    if (list_count == 0) {
        return LIST_SUCCESS;
    }

    if (lists == NULL) {
        return LIST_INVALID_ARGUMENT;
    }

    for (i = 0; i < list_count; ++i) {
        if (lists[i].length > 0 && lists[i].values == NULL) {
            return LIST_INVALID_ARGUMENT;
        }

        if (lists[i].length > SIZE_MAX / sizeof(int)) {
            return LIST_SIZE_OVERFLOW;
        }

        if (lists[i].length > max_length) {
            max_length = lists[i].length;
        }
    }

    for (i = 0; i < list_count; ++i) {
        if (lists[i].length == max_length) {
            if (match_count == SIZE_MAX) {
                return LIST_SIZE_OVERFLOW;
            }

            ++match_count;
        }
    }

    if (match_count > SIZE_MAX / sizeof(*copies)) {
        return LIST_SIZE_OVERFLOW;
    }

    copies = calloc(match_count, sizeof(*copies));
    if (copies == NULL) {
        return LIST_ALLOCATION_FAILURE;
    }

    for (i = 0; i < list_count; ++i) {
        size_t length;

        if (lists[i].length != max_length) {
            continue;
        }

        length = lists[i].length;
        copies[written].length = length;

        if (length > 0) {
            copies[written].values =
                malloc(length * sizeof(*copies[written].values));

            if (copies[written].values == NULL) {
                free_int_lists(copies, match_count);
                return LIST_ALLOCATION_FAILURE;
            }

            for (j = 0; j < length; ++j) {
                copies[written].values[j] = lists[i].values[j];
            }
        }

        ++written;
    }

    *result = copies;
    *result_count = written;
    *maximum_length = max_length;

    return LIST_SUCCESS;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5, 6, 7, 8};
    const int third[] = {9, 10};
    const int fourth[] = {11, 12, 13, 14, 15};
    const IntListView lists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])},
        {fourth, sizeof(fourth) / sizeof(fourth[0])}
    };
    IntList *longest_lists = NULL;
    size_t longest_count = 0;
    size_t maximum_length = 0;
    size_t i;
    size_t j;
    ListStatus status;

    status = find_max_length_lists(
        lists,
        sizeof(lists) / sizeof(lists[0]),
        &longest_lists,
        &longest_count,
        &maximum_length
    );

    if (status != LIST_SUCCESS) {
        (void)fprintf(stderr, "Unable to find maximum-length lists.\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum length: %zu\n", maximum_length) < 0) {
        free_int_lists(longest_lists, longest_count);
        return EXIT_FAILURE;
    }

    for (i = 0; i < longest_count; ++i) {
        if (printf("List %zu:", i + 1) < 0) {
            free_int_lists(longest_lists, longest_count);
            return EXIT_FAILURE;
        }

        for (j = 0; j < longest_lists[i].length; ++j) {
            if (printf(" %d", longest_lists[i].values[j]) < 0) {
                free_int_lists(longest_lists, longest_count);
                return EXIT_FAILURE;
            }
        }

        if (putchar('\n') == EOF) {
            free_int_lists(longest_lists, longest_count);
            return EXIT_FAILURE;
        }
    }

    free_int_lists(longest_lists, longest_count);
    return EXIT_SUCCESS;
}