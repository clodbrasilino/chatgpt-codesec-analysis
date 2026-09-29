#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *items;
    size_t length;
} IntList;

typedef struct {
    size_t *indices;
    size_t count;
    size_t minimum_length;
} MinimumListResult;

void minimum_list_result_init(MinimumListResult *result)
{
    if (result != NULL) {
        result->indices = NULL;
        result->count = 0;
        result->minimum_length = 0;
    }
}

void minimum_list_result_destroy(MinimumListResult *result)
{
    if (result != NULL) {
        free(result->indices);
        minimum_list_result_init(result);
    }
}

bool find_minimum_length_lists(const IntList *lists, size_t list_count,
                               MinimumListResult *result)
{
    MinimumListResult candidate = {NULL, 0, 0};
    size_t minimum_length;
    size_t match_count = 0;
    size_t output_index = 0;

    if (lists == NULL || list_count == 0 || result == NULL) {
        return false;
    }

    for (size_t i = 0; i < list_count; ++i) {
        if (lists[i].length > 0 && lists[i].items == NULL) {
            return false;
        }
    }

    minimum_length = lists[0].length;

    for (size_t i = 1; i < list_count; ++i) {
        if (lists[i].length < minimum_length) {
            minimum_length = lists[i].length;
        }
    }

    for (size_t i = 0; i < list_count; ++i) {
        if (lists[i].length == minimum_length) {
            ++match_count;
        }
    }

    if (match_count > SIZE_MAX / sizeof(*candidate.indices)) {
        return false;
    }

    candidate.indices = malloc(match_count * sizeof(*candidate.indices));
    if (candidate.indices == NULL) {
        return false;
    }

    for (size_t i = 0; i < list_count; ++i) {
        if (lists[i].length == minimum_length) {
            candidate.indices[output_index++] = i;
        }
    }

    candidate.count = match_count;
    candidate.minimum_length = minimum_length;

    minimum_list_result_destroy(result);
    *result = candidate;

    return true;
}

static bool print_list(const IntList *list)
{
    if (list == NULL || (list->length > 0 && list->items == NULL)) {
        return false;
    }

    if (putchar('[') == EOF) {
        return false;
    }

    for (size_t i = 0; i < list->length; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (printf("%d", list->items[i]) < 0) {
            return false;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    static const int first[] = {1, 2, 3};
    static const int second[] = {4, 5};
    static const int third[] = {6};
    static const int fourth[] = {7};
    static const int fifth[] = {8, 9};

    static const IntList lists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])},
        {fourth, sizeof(fourth) / sizeof(fourth[0])},
        {fifth, sizeof(fifth) / sizeof(fifth[0])}
    };

    MinimumListResult result;
    int status = EXIT_FAILURE;

    minimum_list_result_init(&result);

    if (!find_minimum_length_lists(
            lists, sizeof(lists) / sizeof(lists[0]), &result)) {
        fputs("Unable to find minimum-length lists.\n", stderr);
        goto cleanup;
    }

    if (printf("Minimum length: %zu\n", result.minimum_length) < 0) {
        goto cleanup;
    }

    for (size_t i = 0; i < result.count; ++i) {
        if (!print_list(&lists[result.indices[i]])) {
            goto cleanup;
        }
    }

    if (fflush(stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    minimum_list_result_destroy(&result);
    return status;
}