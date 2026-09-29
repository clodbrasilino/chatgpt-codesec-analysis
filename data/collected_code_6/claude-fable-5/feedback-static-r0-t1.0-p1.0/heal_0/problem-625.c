#include <stdio.h>
#include <stdlib.h>

int swap_first_last(int *arr, size_t size)
{
    int temp;

    if (arr == NULL || size == 0U) {
        return -1;
    }

    if (size == 1U) {
        return 0;
    }

    temp = arr[0];
    arr[0] = arr[size - 1U];
    arr[size - 1U] = temp;

    return 0;
}

static void print_list(const int *arr, size_t size)
{
    size_t i;

    if (arr == NULL) {
        return;
    }

    for (i = 0U; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void)
{
    int list[] = {12, 35, 9, 56, 24};
    size_t size = sizeof(list) / sizeof(list[0]);

    printf("Original list: ");
    print_list(list, size);

    if (swap_first_last(list, size) != 0) {
        fprintf(stderr, "Error: invalid list\n");
        return EXIT_FAILURE;
    }

    printf("Modified list: ");
    print_list(list, size);

    return EXIT_SUCCESS;
}