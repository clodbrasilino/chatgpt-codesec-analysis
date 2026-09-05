#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b)
{
    a = abs(a);
    b = abs(b);

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

int find_array_gcd(const int arr[], size_t size)
{
    int result;
    size_t i;

    if (arr == NULL || size == 0) {
        return 0;
    }

    result = arr[0];
    for (i = 1; i < size; i++) {
        result = gcd(result, arr[i]);
        if (result == 1) {
            break;
        }
    }

    return result;
}

int main(void)
{
    int arr[] = {24, 36, 48, 60};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result;

    result = find_array_gcd(arr, size);
    printf("GCD of array elements: %d\n", result);

    return 0;
}