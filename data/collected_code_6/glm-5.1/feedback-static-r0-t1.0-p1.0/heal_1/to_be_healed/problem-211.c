#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
unsigned int count_0th_nth_bits_set(unsigned int *array, size_t size, unsigned int n) {
    if (array == NULL || size == 0) {
        return 0;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'n>=sizeof(unsigned int)*8' is not redundant
     */
    if (n >= sizeof(unsigned int) * 8) {
        return 0;
    }

    unsigned int count = 0;
    /* Possible weaknesses found:
     *  Shifting signed 32-bit value by 31 bits is implementation-defined behaviour. See condition at line 9. [shiftTooManyBitsSigned]
     *  Either the condition 'n>=sizeof(unsigned int)*8' is redundant or there is signed integer overflow for expression '1<<n'. [integerOverflowCond]
     *  Integer overflow
     *  Shift
     */
    unsigned int mask = 1 | (1 << n);

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