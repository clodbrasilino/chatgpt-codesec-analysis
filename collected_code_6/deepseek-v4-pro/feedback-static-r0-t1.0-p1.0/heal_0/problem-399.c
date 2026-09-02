#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int a;
    unsigned int b;
} Tuple;

unsigned int xor_tuple(Tuple t) {
    return t.a ^ t.b;
}

unsigned int xor_tuples(Tuple *tuples, int count) {
    if (tuples == NULL || count <= 0) {
        return 0;
    }
    
    unsigned int result = 0;
    for (int i = 0; i < count; i++) {
        result ^= xor_tuple(tuples[i]);
    }
    
    return result;
}

int main(void) {
    Tuple tuples[] = {
        {5, 3},
        {10, 6},
        {15, 8},
        {20, 13}
    };
    
    int count = sizeof(tuples) / sizeof(tuples[0]);
    
    printf("Individual XOR results:\n");
    for (int i = 0; i < count; i++) {
        printf("Tuple %d: %u ^ %u = %u\n", i + 1, tuples[i].a, tuples[i].b, xor_tuple(tuples[i]));
    }
    
    unsigned int total_xor = xor_tuples(tuples, count);
    printf("\nTotal XOR across all tuples: %u\n", total_xor);
    
    return 0;
}