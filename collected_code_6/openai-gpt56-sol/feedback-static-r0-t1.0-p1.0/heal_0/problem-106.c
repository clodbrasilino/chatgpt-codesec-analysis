#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int add_list_to_tuples(const Tuple *tuples, const int *list,
                              size_t count, Tuple *result)
{
    if ((count > 0U) &&
        (tuples == NULL || list == NULL || result == NULL)) {
        return EINVAL;
    }

    for (size_t i = 0U; i < count; ++i) {
        if ((list[i] > 0 &&
             (tuples[i].first > INT_MAX - list[i] ||
              tuples[i].second > INT_MAX - list[i])) ||
            (list[i] < 0 &&
             (tuples[i].first < INT_MIN - list[i] ||
              tuples[i].second < INT_MIN - list[i]))) {
            return ERANGE;
        }

        result[i].first = tuples[i].first + list[i];
        result[i].second = tuples[i].second + list[i];
    }

    return 0;
}

int main(void)
{
    const Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    const int list[] = {10, 20, 30};
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    Tuple *result = NULL;
    int status = EXIT_FAILURE;

    if (count != sizeof(list) / sizeof(list[0])) {
        fputs("Input sizes do not match.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*result)) {
        fputs("Allocation size overflow.\n", stderr);
        return EXIT_FAILURE;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    const int error = add_list_to_tuples(tuples, list, count, result);
    if (error == EINVAL) {
        fputs("Invalid argument.\n", stderr);
        goto cleanup;
    }
    if (error == ERANGE) {
        fputs("Integer overflow detected.\n", stderr);
        goto cleanup;
    }
    if (error != 0) {
        fputs("Unexpected error.\n", stderr);
        goto cleanup;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("(%d, %d)\n", result[i].first, result[i].second) < 0) {
            fputs("Output error.\n", stderr);
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(result);
    return status;
}