#include <stdio.h>
#include <stdlib.h>

long long countOddXorPairs(const int* arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    long long even_count = 0;
    long long odd_count = 0;

    for (size_t i = 0; i < n; ++i) {
        if (arr[i] % 2 == 0) {
            even_count++;
        } else {
            odd_count++;
        }
    }

    return even_count * odd_count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    long long result = countOddXorPairs(arr, n);
    
    printf("%lld\n", result);

    return 0;
}