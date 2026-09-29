#include <stdio.h>
#include <stdlib.h>

static size_t count_even(const int *list, size_t length)
{
    size_t count = 0;

    if (list == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (list[i] % 2 == 0) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *list = NULL;

    if (length > 0) {
        list = malloc(length * sizeof(*list));
        if (list == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &list[i]) != 1) {
            free(list);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", count_even(list, length));
    free(list);

    return EXIT_SUCCESS;
}