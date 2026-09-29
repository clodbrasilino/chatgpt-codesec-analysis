#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

bool check_tuple_size(const Tuple *t, size_t k) {
    if (t == NULL) {
        return false;
    }
    return t->size == k;
}

int main(void) {
    int data[] = {1, 2, 3};
    Tuple t;
    t.elements = data;
    t.size = 3;

    size_t k = 3;
    bool result = check_tuple_size(&t, k);

    printf("%s\n", result ? "True" : "False");

    return 0;
}