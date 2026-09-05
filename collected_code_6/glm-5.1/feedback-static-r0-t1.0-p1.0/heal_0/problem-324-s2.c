#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int extract_alternate_sum(Tuple *tuples, size_t size) {
    if (tuples == NULL) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < size; i += 2) {
        sum += tuples[i].a + tuples[i].b;
    }

    return sum;
}

int main(void) {
    Tuple data[] = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8}
    };

    size_t data_size = sizeof(data) / sizeof(data[0]);

    int result = extract_alternate_sum(data, data_size);

    printf("%d\n", result);

    return 0;
}