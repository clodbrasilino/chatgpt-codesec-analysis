#include <stdio.h>
#include <stdlib.h>

int count_0th_nth_bits(const unsigned int *arr, size_t n, unsigned int bit_pos) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    int count = 0;
    unsigned int mask = 1;
    mask |= (1u << bit_pos);

    for (size_t i = 0; i < n; i++) {
        if ((arr[i] & mask) == mask) {
            count++;
        }
    }

    return count;
}

int main(void) {
    unsigned int arr[] = {3, 5, 7, 9, 10, 15, 0, 1, 2};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    unsigned int bit_pos = 3;

    int result = count_0th_nth_bits(arr, n, bit_pos);
    printf("%d\n", result);

    return 0;
}