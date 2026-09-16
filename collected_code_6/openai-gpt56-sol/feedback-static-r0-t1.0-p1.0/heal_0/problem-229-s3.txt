#include <stdio.h>
#include <stdlib.h>

static void rearrange(int array[], size_t length)
{
    size_t next_negative = 0;

    for (size_t i = 0; i < length; ++i) {
        if (array[i] < 0) {
            int temporary = array[i];
            array[i] = array[next_negative];
            array[next_negative] = temporary;
            ++next_negative;
        }
    }
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    rearrange(array, length);

    for (size_t i = 0; i < length; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", array[i]) < 0) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}