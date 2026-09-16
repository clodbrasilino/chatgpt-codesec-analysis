#include <stdio.h>

void bitwise_xor_tuples(const unsigned int *a, const unsigned int *b, unsigned int *result, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        result[i] = a[i] ^ b[i];
    }
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'tuple1' can be declared as const array [constVariable]
     */
    unsigned int tuple1[3] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'tuple2' can be declared as const array [constVariable]
     */
    unsigned int tuple2[3] = {4, 5, 6};
    unsigned int result[3];

    bitwise_xor_tuples(tuple1, tuple2, result, 3);

    for (size_t i = 0; i < 3; ++i) {
        printf("%u ", result[i]);
    }

    return 0;
}