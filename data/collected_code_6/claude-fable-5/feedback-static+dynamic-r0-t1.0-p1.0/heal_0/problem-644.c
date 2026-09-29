#include <stdio.h>
#include <stdlib.h>

int reverse_array_upto(int *arr, size_t size, size_t pos)
{
    size_t i;
    size_t j;
    int temp;

    if (arr == NULL) {
        return -1;
    }

    if (size == 0U || pos == 0U || pos > size) {
        return -1;
    }

    i = 0U;
    j = pos - 1U;

    while (i < j) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }

    return 0;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t pos = 5U;
    size_t k;
    int result;

    result = reverse_array_upto(arr, size, pos);

    if (result != 0) {
        (void)fprintf(stderr, "Error: invalid arguments to reverse_array_upto\n");
        return EXIT_FAILURE;
    }

    for (k = 0U; k < size; k++) {
        if (printf("%d ", arr[k]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (printf("\n") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}