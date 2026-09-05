#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    if (tuple_a->first < tuple_b->first) {
        return -1;
    }
    if (tuple_a->first > tuple_b->first) {
        return 1;
    }
    return 0;
}

void sort_tuples(Tuple *list, size_t size) {
    if (list == NULL || size == 0) {
        return;
    }
    qsort(list, size, sizeof(Tuple), compare_tuples);
}

int main(void) {
    Tuple list[] = {{5, 2}, {2, 8}, {5, 1}, {1, 4}, {2, 9}};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t i;

    sort_tuples(list, size);

    for (i = 0; i < size; i++) {
        printf("(%d, %d)\n", list[i].first, list[i].second);
    }

    return 0;
}