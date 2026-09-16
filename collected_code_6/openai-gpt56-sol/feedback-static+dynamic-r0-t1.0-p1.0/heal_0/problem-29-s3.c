#include <stdio.h>
#include <stdlib.h>

static int find_odd_occurrence(const int *values, size_t count, int *result)
{
    size_t i;
    int odd_value = 0;

    if (values == NULL || result == NULL || count == 0U) {
        return 0;
    }

    for (i = 0U; i < count; ++i) {
        odd_value ^= values[i];
    }

    *result = odd_value;
    return 1;
}

int main(void)
{
    int values[] = {4, 3, 4, 3, 4, 5, 5};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int result;

    if (!find_odd_occurrence(values, count, &result)) {
        fputs("Unable to find the odd-occurring element.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}