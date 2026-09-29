#include <stdio.h>
#include <stddef.h>

int find_equilibrium_index(const int *arr, size_t n)
{
    long long total = 0;
    long long left = 0;
    size_t i;

    if (arr == NULL || n == 0) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        total += arr[i];
    }

    for (i = 0; i < n; i++) {
        total -= arr[i];
        if (left == total) {
            return (int)i;
        }
        left += arr[i];
    }

    return -1;
}

int main(void)
{
    int arr[] = { -7, 1, 5, 2, -4, 3, 0 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int index;

    index = find_equilibrium_index(arr, n);

    if (index >= 0) {
        if (printf("Equilibrium index: %d\n", index) < 0) {
            return 1;
        }
    } else {
        if (printf("No equilibrium index found\n") < 0) {
            return 1;
        }
    }

    return 0;
}