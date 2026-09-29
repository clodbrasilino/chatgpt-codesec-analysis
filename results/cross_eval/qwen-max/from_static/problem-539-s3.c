#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int base;
    int index;
} PowerPair;

int power(int base, int exp) {
    if (exp == 0) return 1;
    int result = 1;
    while (exp > 0) {
        if (exp & 1) result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}

void* map_function(const PowerPair* data) {
    int result = power(data->base, data->index);
    return (void*)(intptr_t)result;
}

int main() {
    PowerPair pairs[] = {{2, 3}, {3, 2}, {5, 1}};
    int n = sizeof(pairs) / sizeof(pairs[0]);
    void* results[n];
    for (int i = 0; i < n; ++i) {
        results[i] = map_function(&pairs[i]);
    }
    for (int i = 0; i < n; ++i) {
        printf("%d^%d = %ld\n", pairs[i].base, pairs[i].index, (intptr_t)results[i]);
    }
    return 0;
}