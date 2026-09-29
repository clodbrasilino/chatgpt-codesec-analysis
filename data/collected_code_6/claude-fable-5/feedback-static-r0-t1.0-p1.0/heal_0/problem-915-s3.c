#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int rearrange(int *arr, size_t n)
{
    size_t j = 0;
    size_t i;

    if (arr == NULL || n == 0U) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        if (arr[i] < 0) {
            if (i != j) {
                swap(&arr[i], &arr[j]);
            }
            j++;
        }
    }

    return 0;
}

static void print_array(const int *arr, size_t n)
{
    size_t i;

    if (arr == NULL) {
        return;
    }

    for (i = 0; i < n; i++) {
        if (printf("%d ", arr[i]) < 0) {
            return;
        }
    }
    (void)printf("\n");
}

int main(void)
{
    int arr[] = { -1, 2, -3, 4, 5, 6, -7, 8, 9 };
    size_t n = sizeof(arr) / sizeof(arr[0]);

    (void)printf("Original array: ");
    print_array(arr, n);

    if (rearrange(arr, n) != 0) {
        (void)fprintf(stderr, "Rearrangement failed\n");
        return EXIT_FAILURE;
    }

    (void)printf("Rearranged array: ");
    print_array(arr, n);

    return EXIT_SUCCESS;
}