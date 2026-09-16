#include <stdio.h>
#include <limits.h>
#include <stddef.h>

typedef struct {
    int a;
    int b;
} Tuple;

long long find_max_product(const Tuple *tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        return LLONG_MIN;
    }

    long long max_product = (long long)tuples[0].a * tuples[0].b;

    for (size_t i = 1; i < size; i++) {
        long long current_product = (long long)tuples[i].a * tuples[i].b;
        if (current_product > max_product) {
            max_product = current_product;
        }
    }

    return max_product;
}

int main(void) {
    Tuple list[] = {{1, 5}, {-3, -4}, {2, 3}, {-10, 2}};
    size_t size = sizeof(list) / sizeof(list[0]);

    long long result = find_max_product(list, size);

    if (result == LLONG_MIN) {
        printf("No valid product found.\n");
    } else {
        printf("%lld\n", result);
    }

    return 0;
}