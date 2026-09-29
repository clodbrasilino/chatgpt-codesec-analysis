#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static bool find_first_duplicate(const int *array, size_t length, int *duplicate)
{
    int *sorted = NULL;

    if (array == NULL || duplicate == NULL || length < 2U) {
        return false;
    }

    if (length > SIZE_MAX / sizeof(*sorted)) {
        return false;
    }

    sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        sorted[i] = array[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    for (size_t i = 0U; i < length; ++i) {
        if (bsearch(&array[i], sorted, length, sizeof(*sorted), compare_ints) != NULL) {
            const int *match = bsearch(&array[i], sorted, length, sizeof(*sorted), compare_ints);
            size_t position = (size_t)(match - sorted);
            bool repeated = false;

            if (position > 0U && sorted[position - 1U] == array[i]) {
                repeated = true;
            }

            if (position + 1U < length && sorted[position + 1U] == array[i]) {
                repeated = true;
            }

            if (repeated) {
                *duplicate = array[i];
                free(sorted);
                return true;
            }
        }
    }

    free(sorted);
    return false;
}

int main(void)
{
    const int values[] = {4, 7, 2, 9, 7, 3, 2};
    const size_t length = sizeof(values) / sizeof(values[0]);
    int duplicate = 0;

    if (find_first_duplicate(values, length, &duplicate)) {
        if (printf("%d\n", duplicate) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No duplicate found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}