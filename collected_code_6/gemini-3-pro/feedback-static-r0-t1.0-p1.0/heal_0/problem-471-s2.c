#include <stdio.h>
#include <stdlib.h>

int calculate_remainder(const int *arr, size_t size, int n, int *result) {
    if (arr == NULL || result == NULL || n == 0) {
        return -1;
    }

    long long current_remainder = 1;
    for (size_t i = 0; i < size; ++i) {
        current_remainder = (current_remainder * (arr[i] % n)) % n;
    }

    if (current_remainder < 0) {
        current_remainder += (n < 0 ? -n : n);
    }

    *result = (int)current_remainder;
    return 0;
}

int main(void) {
    int arr[] = {100, 10, 5, 25, 35, 14};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int n = 11;
    int result = 0;

    int status = calculate_remainder(arr, size, n, &result);

    if (status != 0) {
        fprintf(stderr, "Invalid arguments provided.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}