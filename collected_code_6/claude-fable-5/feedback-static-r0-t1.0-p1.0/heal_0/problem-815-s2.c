#include <stdio.h>
#include <stdlib.h>

int sort012(int *arr, size_t n)
{
    size_t count0 = 0;
    size_t count1 = 0;
    size_t count2 = 0;
    size_t i;

    if (arr == NULL) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        if (arr[i] == 0) {
            count0++;
        } else if (arr[i] == 1) {
            count1++;
        } else if (arr[i] == 2) {
            count2++;
        } else {
            return -1;
        }
    }

    for (i = 0; i < count0; i++) {
        arr[i] = 0;
    }
    for (i = count0; i < count0 + count1; i++) {
        arr[i] = 1;
    }
    for (i = count0 + count1; i < n; i++) {
        arr[i] = 2;
    }

    return 0;
}

int main(void)
{
    int arr[] = {2, 0, 1, 2, 1, 0, 0, 2, 1, 1};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t i;

    if (sort012(arr, n) != 0) {
        fprintf(stderr, "Error: invalid input array\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++) {
        if (printf("%d ", arr[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (printf("\n") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}