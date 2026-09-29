#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static void swap_ints(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static size_t next_gap(size_t gap)
{
    gap = (gap * 10U) / 13U;
    if (gap < 1U) {
        gap = 1U;
    }
    return gap;
}

void comb_sort(int *arr, size_t n)
{
    size_t gap;
    bool swapped;
    size_t i;

    if (arr == NULL || n < 2U) {
        return;
    }

    gap = n;
    swapped = true;

    while (gap != 1U || swapped) {
        gap = next_gap(gap);
        swapped = false;
        for (i = 0U; i + gap < n; i++) {
            if (arr[i] > arr[i + gap]) {
                swap_ints(&arr[i], &arr[i + gap]);
                swapped = true;
            }
        }
    }
}

int main(void)
{
    size_t n = 10U;
    size_t i;
    int *data;
    int values[] = { 42, -7, 19, 0, 88, -33, 5, 61, 12, -1 };

    data = malloc(n * sizeof(*data));
    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < n; i++) {
        data[i] = values[i];
    }

    comb_sort(data, n);

    for (i = 0U; i < n; i++) {
        if (printf("%d ", data[i]) < 0) {
            free(data);
            return EXIT_FAILURE;
        }
    }

    if (printf("\n") < 0) {
        free(data);
        return EXIT_FAILURE;
    }

    free(data);
    return EXIT_SUCCESS;
}