#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int find_max_product(Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return 0;
    }

    int max_product = tuples[0].a * tuples[0].b;

    for (size_t i = 1; i < count; i++) {
        int product = tuples[i].a * tuples[i].b;
        if (product > max_product) {
            max_product = product;
        }
    }

    return max_product;
}

int main(void) {
    Tuple data[] = {{1, 2}, {3, 4}, {-5, -6}, {7, 1}};
    size_t count = sizeof(data) / sizeof(data[0]);

    int result = find_max_product(data, count);

    printf("%d\n", result);

    return 0;
}