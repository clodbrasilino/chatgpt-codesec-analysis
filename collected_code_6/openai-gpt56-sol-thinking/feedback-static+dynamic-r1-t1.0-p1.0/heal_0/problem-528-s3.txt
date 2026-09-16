#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *values;
    size_t length;
} IntList;

int find_minimum_length_lists(
    const IntList *lists,
    size_t list_count,
    size_t **indices,
    size_t *index_count,
    size_t *minimum_length
) {
    size_t minimum;
    size_t matches = 0;
    size_t *result;
    size_t i;
    size_t position = 0;

    if (indices == NULL || index_count == NULL || minimum_length == NULL) {
        return -1;
    }

    *indices = NULL;
    *index_count = 0;
    *minimum_length = 0;

    if (list_count == 0) {
        return 0;
    }

    if (lists == NULL) {
        return -1;
    }

    for (i = 0; i < list_count; ++i) {
        if (lists[i].length > 0 && lists[i].values == NULL) {
            return -1;
        }
    }

    minimum = lists[0].length;

    for (i = 1; i < list_count; ++i) {
        if (lists[i].length < minimum) {
            minimum = lists[i].length;
        }
    }

    for (i = 0; i < list_count; ++i) {
        if (lists[i].length == minimum) {
            ++matches;
        }
    }

    if (matches > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = malloc(matches * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (i = 0; i < list_count; ++i) {
        if (lists[i].length == minimum) {
            result[position++] = i;
        }
    }

    *indices = result;
    *index_count = matches;
    *minimum_length = minimum;

    return 0;
}

static int print_list(const IntList *list) {
    size_t i;

    if (putchar('[') == EOF) {
        return -1;
    }

    for (i = 0; i < list->length; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (printf("%d", list->values[i]) < 0) {
            return -1;
        }
    }

    if (putchar(']') == EOF) {
        return -1;
    }

    return 0;
}

int main(void) {
    const int values1[] = {1, 2, 3};
    const int values2[] = {4};
    const int values3[] = {5, 6};
    const int values4[] = {7};
    const IntList lists[] = {
        {values1, sizeof(values1) / sizeof(values1[0])},
        {values2, sizeof(values2) / sizeof(values2[0])},
        {values3, sizeof(values3) / sizeof(values3[0])},
        {values4, sizeof(values4) / sizeof(values4[0])}
    };
    const size_t list_count = sizeof(lists) / sizeof(lists[0]);
    size_t *indices = NULL;
    size_t index_count = 0;
    size_t minimum_length = 0;
    size_t i;
    int status = EXIT_FAILURE;

    if (find_minimum_length_lists(
            lists,
            list_count,
            &indices,
            &index_count,
            &minimum_length) != 0) {
        fputs("Unable to find minimum-length lists.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Minimum length: %zu\n", minimum_length) < 0) {
        goto cleanup;
    }

    for (i = 0; i < index_count; ++i) {
        if (printf("List %zu: ", indices[i]) < 0) {
            goto cleanup;
        }

        if (print_list(&lists[indices[i]]) != 0) {
            goto cleanup;
        }

        if (putchar('\n') == EOF) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(indices);
    return status;
}