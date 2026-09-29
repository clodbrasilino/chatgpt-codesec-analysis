#include <stdio.h>
#include <stddef.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
long long min_swaps_to_sort(int arr[], size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    long long count_zeros = 0;
    long long swaps = 0;

    for (size_t i = n; i > 0; i--) {
        if (arr[i - 1] == 0) {
            count_zeros++;
        } else if (arr[i - 1] == 1) {
            swaps += count_zeros;
        } else {
            return -1;
        }
    }

    return swaps;
}

int main(void) {
    int arr[] = {1, 0, 1, 0, 0, 1, 0};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    long long result = min_swaps_to_sort(arr, n);

    if (result != -1) {
        printf("Minimum swaps: %lld\n", result);
    } else {
        printf("Invalid array elements\n");
    }

    return 0;
}