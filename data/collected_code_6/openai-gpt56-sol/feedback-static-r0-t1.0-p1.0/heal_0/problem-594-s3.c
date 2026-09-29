#include <stdio.h>
#include <stdlib.h>

int find_difference(const int *list, size_t length, int *difference)
{
    int first_even = 0;
    int first_odd = 0;
    int even_found = 0;
    int odd_found = 0;

    if (list == NULL || difference == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length && (!even_found || !odd_found); ++i) {
        if (list[i] % 2 == 0) {
            if (!even_found) {
                first_even = list[i];
                even_found = 1;
            }
        } else if (!odd_found) {
            first_odd = list[i];
            odd_found = 1;
        }
    }

    if (!even_found || !odd_found) {
        return 0;
    }

    *difference = first_even - first_odd;
    return 1;
}

int main(void)
{
    size_t length;
    int *list = NULL;
    int difference;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(*list)) {
        return EXIT_FAILURE;
    }

    list = malloc(length * sizeof(*list));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &list[i]) != 1) {
            free(list);
            return EXIT_FAILURE;
        }
    }

    if (!find_difference(list, length, &difference)) {
        free(list);
        return EXIT_FAILURE;
    }

    printf("%d\n", difference);
    free(list);

    return EXIT_SUCCESS;
}