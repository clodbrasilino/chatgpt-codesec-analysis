#include <stdio.h>
#include <stdlib.h>

long long find_remainder(const long long arr[], size_t len, long long n)
{
    long long result = 1;
    size_t i;

    if (n == 0) {
        fprintf(stderr, "Error: division by zero\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < len; i++) {
        long long value = arr[i] % n;
        if (value < 0) {
            value += (n > 0) ? n : -n;
        }
        result = (result * value) % n;
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

    if (printf("Remainder: %lld\n", remainder) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}