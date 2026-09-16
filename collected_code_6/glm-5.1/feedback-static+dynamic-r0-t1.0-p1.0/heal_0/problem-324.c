#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int extract_alternate_sum(Tuple *tuples, size_t count) {
    int sum_a = 0;
    int sum_b = 0;

    if (tuples == NULL && count > 0) {
        return 0;
    }

    for (size_t i = 0; i < count; i++) {
        if (i % 2 == 0) {
            sum_a += tuples[i].a;
            sum_b += tuples[i].b;
        } else {
            sum_a += tuples[i].b;
            sum_b += tuples[i].a;
        }
    }

    return sum_a + sum_b;
}

int main(void) {
    Tuple data[] = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8}
    };
    size_t data_count = sizeof(data) / sizeof(data[0]);

    int result = extract_alternate_sum(data, data_count);
    printf("%d\n", result);

    return 0;
}