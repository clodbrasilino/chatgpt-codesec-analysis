#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

bool tuple_contains(const Tuple *t, int target) {
    if (t == NULL || t->elements == NULL) {
        return false;
    }

    for (size_t i = 0; i < t->size; i++) {
        if (t->elements[i] == target) {
            return true;
        }
    }

    return false;
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5};
    Tuple t = {data, sizeof(data) / sizeof(data[0])};

    bool found = tuple_contains(&t, 3);
    printf("%d\n", found);

    found = tuple_contains(&t, 10);
    printf("%d\n", found);

    found = tuple_contains(NULL, 1);
    printf("%d\n", found);

    return 0;
}