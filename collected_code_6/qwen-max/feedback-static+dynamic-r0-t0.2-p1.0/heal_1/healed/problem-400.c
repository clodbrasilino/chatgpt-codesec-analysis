#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Tuple;

int tuple_compare(const void *a, const void *b) {
    const Tuple *tupleA = (const Tuple *)a;
    const Tuple *tupleB = (const Tuple *)b;
    if (tupleA->a != tupleB->a) return tupleA->a - tupleB->a;
    return tupleA->b - tupleB->b;
}

void count_unique_tuples(Tuple *tuples, int n, int *unique_count, Tuple **unique_tuples) {
    qsort(tuples, n, sizeof(Tuple), tuple_compare);
    *unique_count = 0;
    for (int i = 0; i < n; ++i) {
        if (i == 0 || tuples[i].a != tuples[i-1].a || tuples[i].b != tuples[i-1].b) {
            unique_tuples[*unique_count] = (Tuple *)malloc(sizeof(Tuple));
            unique_tuples[*unique_count]->a = tuples[i].a;
            unique_tuples[*unique_count]->b = tuples[i].b;
            (*unique_count)++;
        }
    }
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {1, 2}, {5, 6}, {3, 4}, {3, 4}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    int unique_count;
    Tuple *unique_tuples[n];

    count_unique_tuples(tuples, n, &unique_count, unique_tuples);

    for (int i = 0; i < unique_count; ++i) {
        int count = 0;
        for (int j = 0; j < n; ++j) {
            if (tuples[j].a == unique_tuples[i]->a && tuples[j].b == unique_tuples[i]->b) {
                count++;
            }
        }
        printf("Tuple (%d, %d) appears %d times\n", unique_tuples[i]->a, unique_tuples[i]->b, count);
        free(unique_tuples[i]);
    }

    return 0;
}