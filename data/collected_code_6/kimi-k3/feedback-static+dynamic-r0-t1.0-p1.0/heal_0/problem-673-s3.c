#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int convert_to_single_int(const int *arr, size_t size, int *result)
{
    if (arr == NULL || result == NULL || size == 0)
        return -1;

    long long value = 0;

    for (size_t i = 0; i < size; i++) {
        if (arr[i] < 0 || arr[i] > 9)
            return -2;

        if (value > (LLONG_MAX - arr[i]) / 10)
            return -3;

        value = value * 10 + arr[i];
    }

    if (value > INT_MAX)
        return -4;

    *result = (int)value;
    return 0;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result = 0;

    int status = convert_to_single_int(arr, size, &result);
    if (status == 0) {
        printf("%d\n", result);
    } else {
        printf("Error: %d\n", status);
    }

    return 0;
}