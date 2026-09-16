#include <stdio.h>
#include <stdlib.h>

long long count_even_xor_pairs(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }

    long long evenCount = 0;
    long long oddCount = 0;

    for (size_t i = 0; i < size; ++i) {
        if (arr[i] % 2 == 0) {
            evenCount++;
        } else {
            oddCount++;
        }
    }

    long long evenPairs = (evenCount * (evenCount - 1)) / 2;
    long long oddPairs = (oddCount * (oddCount - 1)) / 2;

    return evenPairs + oddPairs;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    long long result = count_even_xor_pairs(arr, size);
    
    printf("Number of pairs with even XOR: %lld\n", result);

    return 0;
}