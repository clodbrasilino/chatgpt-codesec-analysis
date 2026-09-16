#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'b' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'a' can be declared as pointer to const [constParameterPointer]
 */
void bitwise_xor_tuples(unsigned int *a, unsigned int *b, unsigned int *result, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        result[i] = a[i] ^ b[i];
    }
}

int main() {
    unsigned int tuple1[3] = {1, 2, 3};
    unsigned int tuple2[3] = {4, 5, 6};
    unsigned int result[3];

    bitwise_xor_tuples(tuple1, tuple2, result, 3);

    for (size_t i = 0; i < 3; ++i) {
        printf("%u ", result[i]);
    }

    return 0;
}