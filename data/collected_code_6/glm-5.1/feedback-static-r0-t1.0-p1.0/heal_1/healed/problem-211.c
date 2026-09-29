#include <stdio.h>
#include <stdlib.h>

unsigned int count_0th_nth_bits_set(const unsigned int *array, size_t size, unsigned int n) {
    if (array == NULL || size == 0) {
        return 0;
    }

    if (n >= sizeof(unsigned int) * 8) {
        return 0;
    }

    unsigned int mask = 1U | (1U << n);

    unsigned int count = 0;
    for (size_t i = 0; i < size; i++) {
        if ((array[i] & mask) == mask) {
            count++;
        }
    }

    return count;
}

int main(void) {
    unsigned int data[] = {3, 5, 7, 9, 15, 17};
    size_t data_size = sizeof(data) / sizeof(data[0]);
    unsigned int n = 3;

    unsigned int result = count_0th_nth_bits_set(data, data_size, n);
    printf("%u\n", result);

    return 0;
}