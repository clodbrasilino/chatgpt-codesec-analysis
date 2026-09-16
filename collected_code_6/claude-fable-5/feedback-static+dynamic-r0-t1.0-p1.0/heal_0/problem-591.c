#include <stdio.h>
#include <stdlib.h>

int swap_first_last(int *arr, size_t n)
{
    int tmp;

    if (arr == NULL || n == 0) {
        return -1;
    }

    if (n == 1) {
        return 0;
    }

    tmp = arr[0];
    arr[0] = arr[n - 1];
    arr[n - 1] = tmp;

    return 0;
}

int main(void)
{
    int list[] = {10, 20, 30, 40, 50};
    size_t n = sizeof(list) / sizeof(list[0]);
    size_t i;

    if (swap_first_last(list, n) != 0) {
        fprintf(stderr, "Error: invalid list\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++) {
        printf("%d", list[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");

    return EXIT_SUCCESS;
}