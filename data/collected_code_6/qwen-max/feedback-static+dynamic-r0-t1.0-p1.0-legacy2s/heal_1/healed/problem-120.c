#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int a;
    int b;
} Pair;

long long max_pair_product(Pair *list, int size) {
    if (size < 2) return LONG_MIN;
    
    long long max_product = LONG_MIN;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            long long product = ((long long)list[i].a * list[j].b) + ((long long)list[i].b * list[j].a);
            if (product > max_product) {
                max_product = product;
            }
        }
    }
    return max_product;
}

int main() {
    Pair pairs[] = {{1, 2}, {3, 4}, {5, 6}};
    int size = 3;
    long long result = max_pair_product(pairs, size);
    if (result == LONG_MIN) {
        printf("No valid pairs found.\n");
    } else {
        printf("Maximum product: %lld\n", result);
    }
    return 0;
}