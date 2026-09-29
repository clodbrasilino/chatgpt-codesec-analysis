#include <stdio.h>
#include <stddef.h>

int swap_first_last(int *arr, size_t len)
{
    int temp;

    if (arr == NULL || len == 0) {
        return -1;
    }

    if (len == 1) {
        return 0;
    }

    temp = arr[0];
    arr[0] = arr[len - 1];
    arr[len - 1] = temp;

    return 0;
}

int main(void)
{
    int list[] = {10, 20, 30, 40, 50};
    size_t len = sizeof(list) / sizeof(list[0]);
    size_t i;

    if (swap_first_last(list, len) != 0) {
        fprintf(stderr, "Error: invalid list\n");
        return 1;
    }

    for (i = 0; i < len; i++) {
        printf("%d", list[i]);
        if (i < len - 1) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}