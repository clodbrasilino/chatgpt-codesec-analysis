#include <stdio.h>
#include <stdlib.h>

static void arrange_negatives_first(int *array, size_t length)
{
    size_t negative_position = 0;

    for (size_t i = 0; i < length; ++i) {
        if (array[i] < 0) {
            int temporary = array[i];
            array[i] = array[negative_position];
            array[negative_position] = temporary;
            ++negative_position;
        }
    }
}

int main(void)
{
    int values[] = {4, -3, 0, 7, -1, -8, 2, 5, -6};
    const size_t length = sizeof(values) / sizeof(values[0]);

    arrange_negatives_first(values, length);

    for (size_t i = 0; i < length; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", values[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}