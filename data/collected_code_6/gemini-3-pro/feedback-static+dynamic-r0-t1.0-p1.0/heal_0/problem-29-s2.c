#include <stdio.h>
#include <stdlib.h>

int findOdd(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    int res = 0;
    for (size_t i = 0; i < size; ++i) {
        res ^= arr[i];
    }

    return res;
}

int main(void) {
    int arr[] = {2, 3, 5, 4, 5, 2, 4, 3, 5, 2, 4, 4, 2};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int oddElement = findOdd(arr, size);

    if (oddElement != -1) {
        printf("%d\n", oddElement);
    }

    return EXIT_SUCCESS;
}