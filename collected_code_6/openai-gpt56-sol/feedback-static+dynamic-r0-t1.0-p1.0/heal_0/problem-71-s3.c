#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void comb_sort(int *values, size_t count)
{
    size_t gap = count;
    int swapped = 1;

    while (gap > 1U || swapped != 0) {
        if (gap > 1U) {
            gap = (gap * 10U) / 13U;
            if (gap < 1U) {
                gap = 1U;
            }
        }

        swapped = 0;

        for (size_t i = 0U; i < count - gap; ++i) {
            size_t j = i + gap;

            if (values[i] > values[j]) {
                int temporary = values[i];
                values[i] = values[j];
                values[j] = temporary;
                swapped = 1;
            }
        }
    }
}

int main(void)
{
    int values[] = {42, 7, 19, -3, 88, 1, 15, 0};
    const size_t count = sizeof(values) / sizeof(values[0]);

    comb_sort(values, count);

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%s%d", i == 0U ? "" : " ", values[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}