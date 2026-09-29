#include <stdio.h>
#include <stdlib.h>

static size_t count_odd_elements(const int *list, size_t length)
{
    size_t count = 0;

    if (list == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (list[i] % 2 != 0) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1) {
        fprintf(stderr, "Failed to read list length.\n");
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "List length is too large.\n");
        return EXIT_FAILURE;
    }

    int *list = NULL;

    if (length > 0) {
        list = malloc(length * sizeof(*list));
        if (list == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &list[i]) != 1) {
            fprintf(stderr, "Failed to read list element.\n");
            free(list);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", count_odd_elements(list, length));

    free(list);
    return EXIT_SUCCESS;
}