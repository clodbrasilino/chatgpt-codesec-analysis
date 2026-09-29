#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool contains(const int *values, size_t count, int target)
{
    for (size_t i = 0; i < count; ++i) {
        if (values[i] == target) {
            return true;
        }
    }

    return false;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected [3, 6, 7, 10], got <no output>
  *  test case 2 failed: expected [34, 36, 11, 25], got <no output>
  *  test case 1 failed: expected [1, 4, 7, 9], got <no output>
  */

static int *find_dissimilar(const int *first, size_t first_count,
                            const int *second, size_t second_count,
                            size_t *result_count)
{
    if (result_count == NULL) {
        return NULL;
    }

    *result_count = 0;

    if ((first == NULL && first_count != 0) ||
        (second == NULL && second_count != 0) ||
        first_count > SIZE_MAX - second_count) {
        return NULL;
    }

    size_t capacity = first_count + second_count;

    if (capacity > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int *result = NULL;

    if (capacity != 0) {
        result = malloc(capacity * sizeof(*result));
        if (result == NULL) {
            return NULL;
        }
    }

    for (size_t i = 0; i < first_count; ++i) {
        if (!contains(second, second_count, first[i]) &&
            !contains(result, *result_count, first[i])) {
            result[(*result_count)++] = first[i];
        }
    }

    for (size_t i = 0; i < second_count; ++i) {
        if (!contains(first, first_count, second[i]) &&
            !contains(result, *result_count, second[i])) {
            result[(*result_count)++] = second[i];
        }
    }

    if (*result_count == 0) {
        free(result);
        return calloc(1, sizeof(int));
    }

    int *resized = realloc(result, *result_count * sizeof(*result));
    return resized != NULL ? resized : result;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 5};
    const int second[] = {4, 5, 6, 7, 8};
    const size_t first_count = sizeof(first) / sizeof(first[0]);
    const size_t second_count = sizeof(second) / sizeof(second[0]);
    size_t result_count = 0;

    int *result = find_dissimilar(first, first_count,
                                  second, second_count,
                                  &result_count);

    if (result == NULL) {
        fputs("Unable to compute dissimilar elements.\n", stderr);
        return EXIT_FAILURE;
    }

    putchar('[');

    for (size_t i = 0; i < result_count; ++i) {
        if (i != 0) {
            fputs(", ", stdout);
        }
        printf("%d", result[i]);
    }

    puts("]");
    free(result);

    return EXIT_SUCCESS;
}