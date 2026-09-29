#include <stdio.h>
#include <stdlib.h>

static void interchange_first_last(int *list, size_t length)
{
    if (list == NULL || length < 2) {
        return;
    }

    int temporary = list[0];
    list[0] = list[length - 1];
    list[length - 1] = temporary;
}

int main(void)
{
    size_t length;

    if (printf("Enter the number of elements: ") < 0 ||
        scanf("%zu", &length) != 1 ||
        length == 0 ||
        length > SIZE_MAX / sizeof(int)) {
        fputs("Invalid list size.\n", stderr);
        return EXIT_FAILURE;
    }

    int *list = malloc(length * sizeof(*list));
    if (list == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Enter %zu integers: ", length) < 0) {
        free(list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &list[i]) != 1) {
            fputs("Invalid input.\n", stderr);
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