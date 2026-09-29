#include <stdio.h>
#include <stdlib.h>

int binary_tuple_to_int(const int *bits, size_t length) {
    int result = 0;
    for (size_t i = 0; i < length; i++) {
        if (bits[i] != 0 && bits[i] != 1) {
            fprintf(stderr, "Error: bit value must be 0 or 1\n");
            exit(EXIT_FAILURE);
        }
        result = (result << 1) | bits[i];
    }
    return result;
}

int main(void) {
    const int bits1[] = {1, 0, 1, 0};
    const int bits2[] = {0, 0, 0, 1};
    const int bits3[] = {1, 1, 1, 1};
    const int bits4[] = {0, 0, 0, 0};
    const int bits5[] = {1};

    const int results[] = {
        binary_tuple_to_int(bits1, 4),
        binary_tuple_to_int(bits2, 4),
        binary_tuple_to_int(bits3, 4),
        binary_tuple_to_int(bits4, 4),
        binary_tuple_to_int(bits5, 1)
    };

    for (int i = 0; i < 5; i++) {
        printf("%d\n", results[i]);
    }

    return 0;
}