#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_sorted(const int *list, size_t length)
{
    size_t i;

    for (i = 1; i < length; ++i) {
        if (list[i - 1] > list[i]) {
            return 0;
        }
    }

    return 1;
}

static int read_list(int **list, size_t length)
{
    int *values;
    size_t i;

    if (list == NULL) {
        return EINVAL;
    }

    *list = NULL;

    if (length == 0) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*values)) {
        return EOVERFLOW;
    }

    values = malloc(length * sizeof(*values));
    if (values == NULL) {
        return ENOMEM;
    }

    for (i = 0; i < length; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            free(values);
            return EINVAL;
        }
    }

    *list = values;
    return 0;
}

int combine_sorted_lists(const int *first, size_t first_length,
                         const int *second, size_t second_length,
                         int **combined, size_t *combined_length)
{
    int *result;
    size_t total_length;
    size_t first_index = 0;
    size_t second_index = 0;
    size_t result_index = 0;

    if (combined == NULL || combined_length == NULL) {
        return EINVAL;
    }

    *combined = NULL;
    *combined_length = 0;

    if ((first_length != 0 && first == NULL) ||
        (second_length != 0 && second == NULL)) {
        return EINVAL;
    }

    if (!is_sorted(first, first_length) ||
        !is_sorted(second, second_length)) {
        return EINVAL;
    }

    if (first_length > SIZE_MAX - second_length) {
        return EOVERFLOW;
    }

    total_length = first_length + second_length;

    if (total_length == 0) {
        return 0;
    }

    if (total_length > SIZE_MAX / sizeof(*result)) {
        return EOVERFLOW;
    }

    result = malloc(total_length * sizeof(*result));
    if (result == NULL) {
        return ENOMEM;
    }

    while (first_index < first_length &&
           second_index < second_length) {
        if (first[first_index] <= second[second_index]) {
            result[result_index++] = first[first_index++];
        } else {
            result[result_index++] = second[second_index++];
        }
    }

    while (first_index < first_length) {
        result[result_index++] = first[first_index++];
    }

    while (second_index < second_length) {
        result[result_index++] = second[second_index++];
    }

    *combined = result;
    *combined_length = total_length;
    return 0;
}

int main(void)
{
    int *first = NULL;
    int *second = NULL;
    int *combined = NULL;
    size_t first_length;
    size_t second_length;
    size_t combined_length = 0;
    size_t i;
    int error;
    int status = EXIT_FAILURE;

    if (scanf("%zu", &first_length) != 1) {
        fputs("Invalid first list length\n", stderr);
        goto cleanup;
    }

    error = read_list(&first, first_length);
    if (error != 0) {
        fprintf(stderr, "Failed to read first list: %s\n",
                strerror(error));
        goto cleanup;
    }

    if (scanf("%zu", &second_length) != 1) {
        fputs("Invalid second list length\n", stderr);
        goto cleanup;
    }

    error = read_list(&second, second_length);
    if (error != 0) {
        fprintf(stderr, "Failed to read second list: %s\n",
                strerror(error));
        goto cleanup;
    }

    error = combine_sorted_lists(first, first_length,
                                 second, second_length,
                                 &combined, &combined_length);
    if (error != 0) {
        fprintf(stderr, "Failed to combine lists: %s\n",
                strerror(error));
        goto cleanup;
    }

    for (i = 0; i < combined_length; ++i) {
        if (i != 0 && putchar(' ') == EOF) {
            goto cleanup;
        }

        if (printf("%d", combined[i]) < 0) {
            goto cleanup;
        }
    }

    if (putchar('\n') == EOF || fflush(stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(combined);
    free(second);
    free(first);
    return status;
}