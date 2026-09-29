#include <stdio.h>
#include <stdlib.h>

long long sum_non_repeated(const int *arr, size_t n)
{
    long long sum = 0;
    size_t i;
    size_t j;
    int repeated;

    if (arr == NULL || n == 0) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        repeated = 0;
        for (j = 0; j < n; j++) {
            if (i != j && arr[i] == arr[j]) {
                repeated = 1;
                break;
            }
        }
        if (!repeated) {
            sum += (long long)arr[i];
        }
    }

    return sum;
}

int main(void)
{
    int data[] = {1, 2, 3, 2, 4, 5, 1, 6};
    size_t n = sizeof(data) / sizeof(data[0]);
    long long result;

    result = sum_non_repeated(data, n);

    if (printf("Sum of non-repeated elements: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}