#include <stdio.h>
#include <stdlib.h>

int find_equilibrium_index(const int arr[], size_t size)
{
    long long total_sum = 0;
    long long left_sum = 0;
    size_t i;

    if (arr == NULL || size == 0) {
        return -1;
    }

    for (i = 0; i < size; i++) {
        total_sum += arr[i];
    }

    for (i = 0; i < size; i++) {
        total_sum -= arr[i];
        if (left_sum == total_sum) {
            return (int)i;
        }
        left_sum += arr[i];
    }

    return -1;
}

int main(void)
{
    int arr[] = {-7, 1, 5, 2, -4, 3, 0};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int index = find_equilibrium_index(arr, size);

    if (index >= 0) {
        printf("Equilibrium index: %d\n", index);
    } else {
        printf("No equilibrium index found\n");
    }

    return 0;
}