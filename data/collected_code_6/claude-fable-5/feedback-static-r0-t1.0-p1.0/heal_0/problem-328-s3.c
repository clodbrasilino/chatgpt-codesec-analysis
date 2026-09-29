#include <stdio.h>
#include <stdlib.h>

static void reverse_range(int *arr, size_t start, size_t end)
{
    while (start < end) {
        int tmp = arr[start];
        arr[start] = arr[end];
        arr[end] = tmp;
        start++;
        end--;
    }
}

int rotate_left(int *arr, size_t size, size_t count)
{
    if (arr == NULL) {
        return -1;
    }
    if (size == 0U) {
        return 0;
    }
    count = count % size;
    if (count == 0U) {
        return 0;
    }
    reverse_range(arr, 0U, count - 1U);
    reverse_range(arr, count, size - 1U);
    reverse_range(arr, 0U, size - 1U);
    return 0;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5, 6, 7};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t rotate_by = 3U;

    if (rotate_left(list, size, rotate_by) != 0) {
        fprintf(stderr, "Rotation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < size; i++) {
        if (printf("%d ", list[i]) < 0) {
            return EXIT_FAILURE;
        }
    }
    if (printf("\n") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}