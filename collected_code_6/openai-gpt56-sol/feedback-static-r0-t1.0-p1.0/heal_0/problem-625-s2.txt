#include <stdio.h>
#include <stdlib.h>

static int interchange_first_last(int *list, size_t length)
{
    if (list == NULL || length < 2) {
        return 0;
    }

    int temporary = list[0];
    list[0] = list[length - 1];
    list[length - 1] = temporary;

    return 1;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *list = malloc(length * sizeof(*list));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &list[i]) != 1) {
            free(list);
            return EXIT_FAILURE;
        }
    }

    interchange_first_last(list, length);

    for (size_t i = 0; i < length; ++i) {
        if (printf("%d%s", list[i], i + 1 == length ? "\n" : " ") < 0) {
            free(list);
            return EXIT_FAILURE;
        }
    }

    free(list);
    return EXIT_SUCCESS;
}