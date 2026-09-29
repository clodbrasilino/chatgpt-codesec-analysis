#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int c;
} Tuple;

int is_all_none(const Tuple *t) {
    return t->a == 0 && t->b == 0 && t->c == 0;
}

Tuple* remove_all_none(Tuple *list, size_t *size) {
    if (*size == 0) return list;

    size_t new_size = 0;
    for (size_t i = 0; i < *size; ++i) {
        if (!is_all_none(&list[i])) {
            list[new_size++] = list[i];
        }
    }

    *size = new_size;
    return list;
}

int main() {
    Tuple tuples[] = {{1, 2, 3}, {0, 0, 0}, {4, 5, 6}, {0, 0, 0}, {7, 8, 9}};
    size_t size = sizeof(tuples) / sizeof(tuples[0]);

    Tuple *filtered_tuples = remove_all_none(tuples, &size);

    for (size_t i = 0; i < size; ++i) {
        printf("(%d, %d, %d)\n", filtered_tuples[i].a, filtered_tuples[i].b, filtered_tuples[i].c);
    }

    return 0;
}