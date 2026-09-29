#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

size_t count_occurrences(const Tuple *t, int target) {
    if (t == NULL || t->elements == NULL) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < t->size; ++i) {
        if (t->elements[i] == target) {
            ++count;
        }
    }
    return count;
}

int main(void) {
    int data[] = {1, 2, 3, 2, 4, 2, 5};
    Tuple t;
    t.elements = data;
    t.size = sizeof(data) / sizeof(data[0]);

    int target = 2;
    size_t occurrences = count_occurrences(&t, target);

    printf("%zu\n", occurrences);

    return 0;
}