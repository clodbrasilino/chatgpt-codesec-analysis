#include <stdio.h>
#include <stdlib.h>

int reverse_array_upto(int *arr, size_t size, size_t pos)
{
    size_t left;
    size_t right;

    if (arr == NULL) {
        return -1;
    }
    if (size == 0U) {
        return -1;
    }
    if (pos == 0U) {
        return -1;
    }
    if (pos > size) {
        return -1;
    }

    left = 0U;
    right = pos - 1U;

    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }

    return 0;
}

static void print_array(const int *arr, size_t size)
{
    size_t i;

    if (arr == NULL) {
        return;
    }

    for (i = 0U; i < size; i++) {
        if (printf("%d ", arr[i]) < 0) {
            return;
        }
    }
    (void)printf("\n");
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t pos = 5U;
    int result;

    (void)printf("Original array: ");
    print_array(arr, size);

    result = reverse_array_upto(arr, size, pos);
    if (result != 0) {
        (void)fprintf(stderr, "Error: invalid arguments for reversal\n");
        return EXIT_FAILURE;
    }

    (void)printf("Array after reversing first %zu elements: ", pos);
    print_array(arr, size);

    return EXIT_SUCCESS;
}