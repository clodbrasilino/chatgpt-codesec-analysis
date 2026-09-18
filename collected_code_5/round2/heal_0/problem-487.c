#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

typedef struct {
    int first;
    int second;
} Tuple;

int compare_tuple(const void* a, const void* b) {
    Tuple* tuple_a = (Tuple*)a;
    Tuple* tuple_b = (Tuple*)b;
    return tuple_a->second - tuple_b->second;
}

void sort_tuples(Tuple* tuples, int size) {
    qsort(tuples, size, sizeof(Tuple), compare_tuple);
}

void print_tuples(Tuple* tuples, int size) {
    for (int i = 0; i < size; i++) {
        printf("(%d, %d)\n", tuples[i].first, tuples[i].second);
    }
}

int main() {
    Tuple tuples[SIZE] = { {1, 5}, {3, 2}, {5, 9}, {8, 1}, {6, 4} };
    sort_tuples(tuples, SIZE);
    print_tuples(tuples, SIZE);
    return 0;
}