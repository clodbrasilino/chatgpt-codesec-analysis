#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static int interchange_first_last(int *list, size_t length)
{
    if (list == NULL || length == 0U) {
        return -1;
    }

    if (length > 1U) {
        int temporary = list[0];
        list[0] = list[length - 1U];
        list[length - 1U] = temporary;
    }

    return 0;
}

int main(void)
{
    size_t length = 0U;

    if (scanf("%zu", &length) != 1 || length == 0U ||
        length > SIZE_MAX / sizeof(int)) {
        fputs("Invalid list length\n", stderr);
        return EXIT_FAILURE;
    }

    int *list = malloc(length * sizeof(*list));
    if (list == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%d", &list[i]) != 1) {
            fputs("Invalid list element\n", stderr);
            free(list);
            return EXIT_FAILURE;
        }
    }

    if (interchange_first_last(list, length) != 0) {
        fputs("Unable to interchange elements\n", stderr);
        free(list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (printf("%d%s", list[i], (i + 1U < length) ? " " : "\n") < 0) {
            fputs("Output error\n", stderr);
            free(list);
            return EXIT_FAILURE;
        }
    }

    free(list);
    return EXIT_SUCCESS;
}