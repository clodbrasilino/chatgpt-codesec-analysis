#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *data;
    size_t length;
} IntList;

typedef enum {
    FIND_OK,
    FIND_INVALID_ARGUMENT,
    FIND_ALLOCATION_FAILURE
} FindStatus;

typedef struct {
    size_t *indices;
    size_t count;
    size_t maximum_length;
    FindStatus status;
} LongestListsResult;

static LongestListsResult find_longest_lists(const IntList *lists, size_t list_count)
{
    LongestListsResult result = {NULL, 0, 0, FIND_OK};
    size_t match_count = 0;
    size_t output_index = 0;

    if (list_count > 0 && lists == NULL) {
        result.status = FIND_INVALID_ARGUMENT;
        return result;
    }

    for (size_t i = 0; i < list_count; ++i) {
        if (lists[i].length > 0 && lists[i].data == NULL) {
            result.status = FIND_INVALID_ARGUMENT;
            return result;
        }

        if (lists[i].length > result.maximum_length) {
            result.maximum_length = lists[i].length;
        }
    }

    for (size_t i = 0; i < list_count; ++i) {
        if (lists[i].length == result.maximum_length) {
            ++match_count;
        }
    }

    if (match_count == 0) {
        return result;
    }

    if (match_count > SIZE_MAX / sizeof(*result.indices)) {
        result.status = FIND_ALLOCATION_FAILURE;
        return result;
    }

    result.indices = malloc(match_count * sizeof(*result.indices));
    if (result.indices == NULL) {
        result.status = FIND_ALLOCATION_FAILURE;
        return result;
    }

    for (size_t i = 0; i < list_count; ++i) {
        if (lists[i].length == result.maximum_length) {
            result.indices[output_index++] = i;
        }
    }

    result.count = match_count;
    return result;
}

static void destroy_longest_lists_result(LongestListsResult *result)
{
    if (result != NULL) {
        free(result->indices);
        result->indices = NULL;
        result->count = 0;
        result->maximum_length = 0;
        result->status = FIND_OK;
    }
}

static bool print_list(const IntList *list)
{
    if (list == NULL || (list->length > 0 && list->data == NULL)) {
        return false;
    }

    if (putchar('[') == EOF) {
        return false;
    }

    for (size_t i = 0; i < list->length; ++i) {
        if (i > 0 && printf(", ") < 0) {
            return false;
        }

        if (printf("%d", list->data[i]) < 0) {
            return false;
        }
    }

    return printf("]\n") >= 0;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5, 6, 7, 8};
    const int third[] = {9, 10};
    const int fourth[] = {11, 12, 13, 14, 15};

    const IntList lists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])},
        {fourth, sizeof(fourth) / sizeof(fourth[0])}
    };

    const size_t list_count = sizeof(lists) / sizeof(lists[0]);
    LongestListsResult result = find_longest_lists(lists, list_count);
    bool output_succeeded = true;

    if (result.status != FIND_OK) {
        fprintf(stderr, "Unable to find the longest lists.\n");
        destroy_longest_lists_result(&result);
        return EXIT_FAILURE;
    }

    if (printf("Maximum length: %zu\n", result.maximum_length) < 0) {
        output_succeeded = false;
    }

    for (size_t i = 0; output_succeeded && i < result.count; ++i) {
        output_succeeded = print_list(&lists[result.indices[i]]);
    }

    destroy_longest_lists_result(&result);

    if (!output_succeeded) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}