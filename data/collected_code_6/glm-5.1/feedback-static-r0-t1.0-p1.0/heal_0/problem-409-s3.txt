#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int a;
    int b;
} Tuple;

int find_min_product(Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return INT_MAX;
    }

    int min_product = INT_MAX;

    for (size_t i = 0; i < count; i++) {
        if (tuples[i].a == INT_MIN && tuples[i].b == INT_MIN) {
            return INT_MAX;
        }
        
        if ((tuples[i].a == INT_MIN && tuples[i].b < 0) || (tuples[i].b == INT_MIN && tuples[i].a < 0)) {
            return INT_MAX;
        }

        long long product = (long long)tuples[i].a * (long long)tuples[i].b;

        if (product > INT_MAX || product < INT_MIN) {
            return INT_MAX;
        }

        if ((int)product < min_product) {
            min_product = (int)product;
        }
    }

    return min_product;
}

int main(void) {
    Tuple tuples[] = {{5, -2}, {3, 4}, {-1, -10}, {7, 0}};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    int result = find_min_product(tuples, count);

    printf("%d\n", result);

    return 0;
}