#include <stdio.h>
#include <stdlib.h>

int multiply_consecutive(const int *list, size_t size, int *result) {
    if (list == NULL || result == NULL) {
        return -1;
    }

    if (size == 0) {
        *result = 1;
        return 0;
    }

    *result = list[0];

    for (size_t i = 1; i < size; i++) {
        *result *= list[i];
    }

    return 0;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    size_t len = sizeof(arr) / sizeof(arr[0]);
    int res;

    if (multiply_consecutive(arr, len, &res) == 0) {
        printf("%d\n", res);
    }

    return 0;
}