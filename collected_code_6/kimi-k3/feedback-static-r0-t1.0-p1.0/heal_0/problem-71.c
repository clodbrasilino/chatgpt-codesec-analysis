#include <stdio.h>
#include <stdlib.h>

int get_next_gap(int gap)
{
    gap = (gap * 10) / 13;
    if (gap < 1) {
        return 1;
    }
    return gap;
}

int comb_sort(int *arr, size_t n)
{
    size_t gap;
    int swapped;
    size_t i;
    int temp;

    if (arr == NULL) {
        return -1;
    }

    if (n == 0) {
        return 0;
    }

    gap = n;
    swapped = 1;

    while (gap != 1 || swapped == 1) {
        gap = (size_t)get_next_gap((int)gap);
        swapped = 0;

        for (i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = 1;
            }
        }
    }

    return 0;
}

int main(void)
{
    int arr[] = {8, 4, 1, 56, 3, -44, 23, -6, 28, 0};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t i;
    int result;

    printf("Original array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    result = comb_sort(arr, n);
    if (result != 0) {
        fprintf(stderr, "Error: comb_sort failed\n");
        return EXIT_FAILURE;
    }

    printf("Sorted array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}