#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

void swap(Tuple *a, Tuple *b) {
    Tuple temp = *a;
    *a = *b;
    *b = temp;
}

void rearrangeTuples(Tuple *tuples, int *order, int size) {
    for (int i = 0; i < size; ++i) {
        if (order[i] != i) {
            int pos = order[i];
            while (pos != i) {
                swap(&tuples[pos], &tuples[order[pos]]);
                int temp = order[pos];
                order[pos] = pos;
                pos = temp;
            }
            swap(&tuples[i], &tuples[order[i]]);
            order[order[i]] = order[i];
        }
    }
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 6}};
    int order[] = {2, 0, 1};
    int size = sizeof(tuples) / sizeof(tuples[0]);

    rearrangeTuples(tuples, order, size);

    for (int i = 0; i < size; ++i) {
        printf("(%d, %d) ", tuples[i].first, tuples[i].second);
    }

    return 0;
}