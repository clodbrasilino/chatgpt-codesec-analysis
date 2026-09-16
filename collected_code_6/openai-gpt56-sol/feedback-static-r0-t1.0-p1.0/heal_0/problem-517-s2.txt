#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int find_largest_positive(const int values[], size_t count, int *largest)
{
    if (values == NULL || largest == NULL || count == 0U) {
        return 0;
    }

    int found = 0;
    int maximum = 0;

    for (size_t i = 0U; i < count; ++i) {
        if (values[i] > 0 && (!found || values[i] > maximum)) {
            maximum = values[i];
            found = 1;
        }
    }

    if (found) {
        *largest = maximum;
    }

    return found;
}

int main(void)
{
    size_t count = 0U;

    if (scanf("%zu", &count) != 1 || count == 0U ||
        count > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Invalid list size.\n");
        return EXIT_FAILURE;
    }

    int *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        long value = 0L;

        errno = 0;
        if (scanf("%ld", &value) != 1 || errno == ERANGE ||
            value < INT_MIN || value > INT_MAX) {
            fprintf(stderr, "Invalid list value.\n");
            free(values);
            return EXIT_FAILURE;
        }

        values[i] = (int)value;
    }

    int largest = 0;
    if (!find_largest_positive(values, count, &largest)) {
        fprintf(stderr, "The list contains no positive numbers.\n");
        free(values);
        return EXIT_FAILURE;
    }

    printf("%d\n", largest);

    free(values);
    return EXIT_SUCCESS;
}