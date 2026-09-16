#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int count_numbers_with_bits_set(int *array, size_t size, unsigned int o, unsigned int n) {
    if (array == NULL || size == 0) {
        return 0;
    }

    int count = 0;
    unsigned int mask = (1U << o) | (1U << n);

    for (size_t i = 0; i < size; i++) {
        if ((array[i] & mask) == mask) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int arr[] = {1, 3, 5, 7, 9, 11, 15};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    unsigned int bit_o = 0;
    unsigned int bit_n = 1;

    int result = count_numbers_with_bits_set(arr, size, bit_o, bit_n);
    printf("%d\n", result);

    return 0;
}