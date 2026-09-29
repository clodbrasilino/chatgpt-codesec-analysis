#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

size_t count_bidirectional_pairs(const Tuple *tuples, size_t size);

size_t count_bidirectional_pairs(const Tuple *tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        return 0;
    }

    size_t count = 0;

    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (tuples[i].a == tuples[j].b && tuples[i].b == tuples[j].a) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {2, 1},
        {5, 6},
        {4, 3},
        {1, 2}
    };
    
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    
    size_t count = count_bidirectional_pairs(tuples, num_tuples);
    
    printf("%zu\n", count);
    
    return 0;
}