#include <stdio.h>
#include <stdlib.h>

size_t count_numbers_with_bits_set(const unsigned int *arr, size_t size, unsigned int n) {
    if (arr == NULL || n >= (sizeof(unsigned int) * 8)) {
        return 0;
    }

    size_t count = 0;
    unsigned int mask0 = 1U;
    unsigned int maskN = 1U << n;

    for (size_t i = 0; i < size; ++i) {
        if ((arr[i] & mask0) && (arr[i] & maskN)) {
            count++;
        }
    }

    return count;
}

int main(void) {
    unsigned int data[] = {1, 3, 5, 9, 17, 33};
    size_t size = sizeof(data) / sizeof(data[0]);
    unsigned int n = 3; 

    size_t result = count_numbers_with_bits_set(data, size, n);
    printf("%zu\n", result);

    n = 4;
    result = count_numbers_with_bits_set(data, size, n);
    printf("%zu\n", result);

    result = count_numbers_with_bits_set(NULL, size, n);
    printf("%zu\n", result);

    return 0;
}