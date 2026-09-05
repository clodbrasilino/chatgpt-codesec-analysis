#include <stdio.h>
#include <stdlib.h>

long long count_even_xor_pairs(int *arr, size_t n) {
    size_t even_count = 0;
    size_t odd_count = 0;
    size_t i;

    if (arr == NULL || n == 0) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        if ((arr[i] & 1) == 0) {
            even_count++;
        } else {
            odd_count++;
        }
    }

    return (long long)even_count * (even_count - 1) / 2 + (long long)odd_count * (odd_count - 1) / 2;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    long long result1 = count_even_xor_pairs(arr1, n1);
    printf("%lld\n", result1);

    int arr2[] = {2, 4, 6, 8, 10};
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    long long result2 = count_even_xor_pairs(arr2, n2);
    printf("%lld\n", result2);

    int arr3[] = {1, 3, 5, 7};
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);
    long long result3 = count_even_xor_pairs(arr3, n3);
    printf("%lld\n", result3);

    long long result4 = count_even_xor_pairs(NULL, n1);
    printf("%lld\n", result4);

    return 0;
}