#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static bool find_first_duplicate(const int *array, size_t length, int *duplicate)
{
    int *sorted = NULL;
    bool found = false;
    size_t i;

    if (array == NULL || duplicate == NULL || length < 2 ||
        length > SIZE_MAX / sizeof(*sorted)) {
        return false;
    }

    sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        return false;
    }

    for (i = 0; i < length; ++i) {
        sorted[i] = array[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    for (i = 1; i < length; ++i) {
        if (sorted[i] == sorted[i - 1]) {
            *duplicate = sorted[i];
            found = true;
            break;
        }
    }

    free(sorted);
    return found;
}

int main(void)
{
    const int array[] = {4, 2, 7, 5, 2, 7};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int duplicate;

    if (find_first_duplicate(array, length, &duplicate)) {
        printf("First duplicate: %d\n", duplicate);
        return EXIT_SUCCESS;
    }

    puts("No duplicate found.");
    return EXIT_SUCCESS;
}