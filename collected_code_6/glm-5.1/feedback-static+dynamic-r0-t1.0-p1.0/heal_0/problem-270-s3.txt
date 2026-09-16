#include <stdio.h>
#include <stdlib.h>

int sum_even_at_even_positions(const int *arr, size_t size) {
    if (arr == NULL) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 1; i < size; i += 2) {
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }

    return sum;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int result = sum_even_at_even_positions(arr, size);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}