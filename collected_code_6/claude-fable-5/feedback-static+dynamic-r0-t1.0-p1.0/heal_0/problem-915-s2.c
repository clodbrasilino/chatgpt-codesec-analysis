#include <stdio.h>
#include <stddef.h>

static void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void rearrange(int *arr, size_t n)
{
    size_t j = 0;
    size_t i;

    if (arr == NULL || n == 0U) {
        return;
    }

    for (i = 0; i < n; i++) {
        if (arr[i] < 0) {
            if (i != j) {
                swap(&arr[i], &arr[j]);
            }
            j++;
        }
    }
}

static int print_array(const int *arr, size_t n)
{
    size_t i;

    if (arr == NULL) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        if (printf("%d ", arr[i]) < 0) {
            return -1;
        }
    }

    if (printf("\n") < 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    int arr[] = { -12, 11, -13, -5, 6, -7, 5, -3, -6 };
    size_t n = sizeof(arr) / sizeof(arr[0]);

    if (printf("Original array: ") < 0) {
        return 1;
    }

    if (print_array(arr, n) != 0) {
        return 1;
    }

    rearrange(arr, n);

    if (printf("Rearranged array: ") < 0) {
        return 1;
    }

    if (print_array(arr, n) != 0) {
        return 1;
    }

    return 0;
}