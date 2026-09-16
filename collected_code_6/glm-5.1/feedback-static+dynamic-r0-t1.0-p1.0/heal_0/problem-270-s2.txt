#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sum_even_at_even_positions(const int *arr, size_t size) {
    if (arr == NULL) {
        return 0;
    }

    long long sum = 0;

    for (size_t i = 0; i < size; i += 2) {
        if (arr[i] % 2 == 0) {
            if ((sum > 0 && arr[i] > INT_MAX - sum) || (sum < 0 && arr[i] < INT_MIN - sum)) {
                return 0;
            }
            sum += arr[i];
        }
    }

    if (sum > INT_MAX || sum < INT_MIN) {
        return 0;
    }

    return (int)sum;
}

int main(void) {
    int arr1[] = {2, 5, 8, 3, 6, 9};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = sum_even_at_even_positions(arr1, size1);
    printf("%d\n", result1);

    int arr2[] = {1, 4, 7, 2, 5, 8};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = sum_even_at_even_positions(arr2, size2);
    printf("%d\n", result2);

    int result3 = sum_even_at_even_positions(NULL, size2);
    printf("%d\n", result3);

    return 0;
}