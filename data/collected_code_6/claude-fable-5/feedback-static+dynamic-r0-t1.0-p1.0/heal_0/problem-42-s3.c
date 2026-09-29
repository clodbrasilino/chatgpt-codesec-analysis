#include <stdio.h>
#include <stdlib.h>

long sum_of_repeated_elements(const int *arr, size_t n)
{
    long sum = 0;
    size_t i;
    size_t j;

    if (arr == NULL || n == 0) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        size_t count = 0;
        for (j = 0; j < n; j++) {
            if (arr[j] == arr[i]) {
                count++;
            }
        }
        if (count > 1) {
            sum += arr[i];
        }
    }

    return sum;
}

int main(void)
{
    int data[] = { 1, 2, 3, 1, 1, 4, 5, 6, 6 };
    size_t n = sizeof(data) / sizeof(data[0]);
    long result;

    result = sum_of_repeated_elements(data, n);

    if (printf("Sum of repeated elements: %ld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}