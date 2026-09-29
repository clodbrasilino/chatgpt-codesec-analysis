#include <stdio.h>
#include <stdlib.h>

static void swap_adjacent(int *values, size_t count)
{
    if (values == NULL) {
        return;
    }

    for (size_t i = 0; i + 1 < count; i += 2) {
        int temporary = values[i];
        values[i] = values[i + 1];
        values[i + 1] = temporary;
    }
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *values = count == 0 ? NULL : malloc(count * sizeof(*values));
    if (count != 0 && values == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    swap_adjacent(values, count);

    for (size_t i = 0; i < count; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", values[i]) < 0) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}