#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

size_t count_occurrences(const Tuple *tuple, int target) {
    if (tuple == NULL || tuple->elements == NULL) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < tuple->size; ++i) {
        if (tuple->elements[i] == target) {
            ++count;
        }
    }
    return count;
}

int main(void) {
    int data[] = {1, 2, 3, 2, 4, 2, 5};
    Tuple my_tuple;
    my_tuple.elements = data;
    my_tuple.size = sizeof(data) / sizeof(data[0]);

    int target = 2;
    size_t occurrences = count_occurrences(&my_tuple, target);

    printf("%zu\n", occurrences);

    return 0;
}