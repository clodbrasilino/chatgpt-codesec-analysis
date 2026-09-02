#include <stdio.h>
#include <stdint.h>

int count_set_bits(uint32_t n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int count_odd_set_bits(int *arr, int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        if (count_set_bits(arr[i]) % 2 != 0) {
            result++;
        }
    }
    return result;
}

int main() {
    int arr[] = {3, 7, 15, 2, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int odd_count = count_odd_set_bits(arr, size);
    printf("Number of integers with odd number of set bits: %d\n", odd_count);
    return 0;
}