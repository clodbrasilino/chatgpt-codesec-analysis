#include <stdio.h>
#include <stdlib.h>

static void reverse(int *arr, size_t start, size_t end)
{
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int rotate_left(int *arr, size_t size, size_t count)
{
    if (arr == NULL || size == 0) {
        return -1;
    }

    count = count % size;

    if (count == 0) {
        return 0;
    }

    reverse(arr, 0, count - 1);
    reverse(arr, count, size - 1);
    reverse(arr, 0, size - 1);

    return 0;
}

static void print_list(const int *arr, size_t size)
{
    size_t i;

    for (i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i + 1 < size) {
            printf(" ");
        }
    }
    printf("\n");
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5, 6, 7};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t rotate_by = 3;

    printf("Original list: ");
    print_list(list, size);

    if (rotate_left(list, size, rotate_by) != 0) {
        fprintf(stderr, "Error: rotation failed\n");
        return EXIT_FAILURE;
    }

    printf("Rotated list:  ");
    print_list(list, size);

    return EXIT_SUCCESS;
}