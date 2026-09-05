#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    const unsigned char *bits;
    size_t length;
} BinaryTuple;

int binary_tuple_to_int(const BinaryTuple *tuple, int *result) {
    if (tuple == NULL || result == NULL) {
        return -1;
    }
    
    if (tuple->bits == NULL && tuple->length > 0) {
        return -1;
    }
    
    if (tuple->length == 0) {
        *result = 0;
        return 0;
    }
    
    if (tuple->length > sizeof(int) * CHAR_BIT) {
        return -1;
    }
    
    int value = 0;
    for (size_t i = 0; i < tuple->length; i++) {
        if (tuple->bits[i] != 0 && tuple->bits[i] != 1) {
            return -1;
        }
        
        if (value > (INT_MAX >> 1)) {
            return -1;
        }
        
        value = (value << 1) | (int)tuple->bits[i];
    }
    
    *result = value;
    return 0;
}

int main(void) {
    const unsigned char bits[] = {1, 0, 1, 1};
    BinaryTuple tuple = {bits, sizeof(bits) / sizeof(bits[0])};
    int result = 0;
    
    if (binary_tuple_to_int(&tuple, &result) != 0) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Binary: ");
    for (size_t i = 0; i < tuple.length; i++) {
        printf("%u", (unsigned int)tuple.bits[i]);
    }
    printf("\nInteger: %d\n", result);
    
    return EXIT_SUCCESS;
}