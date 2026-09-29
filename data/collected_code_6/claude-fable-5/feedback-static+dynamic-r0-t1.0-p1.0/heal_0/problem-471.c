#include <stdio.h>
#include <stdlib.h>

long long find_remainder(const long long arr[], size_t len, long long n)
{
    long long result = 0;
    size_t i;

    if (arr == NULL || len == 0 || n == 0) {
        return -1;
    }

    result = 1;
    for (i = 0; i < len; i++) {
        long long term = arr[i] % n;
        if (term < 0) {
            term += (n > 0) ? n : -n;
        }
        result = (result * term) % n;
        if (result < 0) {
            result += (n > 0) ? n : -n;
        }
    }

    return result;
}

int main(void)
{
    long long arr[] = {100, 10, 5, 25, 35, 14};
    size_t len = sizeof(arr) / sizeof(arr[0]);
    long long n = 11;
    long long remainder;

    remainder = find_remainder(arr, len, n);
    if (remainder < 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("Remainder: %lld\n", remainder) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}