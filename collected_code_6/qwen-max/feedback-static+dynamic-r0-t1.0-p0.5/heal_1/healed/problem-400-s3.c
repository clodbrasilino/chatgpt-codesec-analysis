#include <stdio.h>
#include <stdlib.h>

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

void count_unique_tuples(Tuple *tuples, int n, int *count, Tuple **unique) {
    qsort(tuples, n, sizeof(Tuple), tuple_compare);
    *count = 1;
    for (int i = 1; i < n; i++) {
        if (tuples[i].a != tuples[i-1].a || tuples[i].b != tuples[i-1].b) {
            (*count)++;
        }
    }
    *unique = (Tuple *)malloc(*count * sizeof(Tuple));
    if (*unique == NULL) {
        exit(EXIT_FAILURE);
    }
    int index = 0;
    (*unique)[index++] = tuples[0];
    for (int i = 1; i < n; i++) {
        if (tuples[i].a != tuples[i-1].a || tuples[i].b != tuples[i-1].b) {
            (*unique)[index++] = tuples[i];
        }
    }
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {1, 2}, {5, 6}, {3, 4}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    int count;
    Tuple *unique;
    count_unique_tuples(tuples, n, &count, &unique);

    for (int i = 0; i < count; i++) {
        int frequency = 0;
        for (int j = 0; j < n; j++) {
            if (tuples[j].a == unique[i].a && tuples[j].b == unique[i].b) {
                frequency++;
            }
        }
        printf("Tuple (%d, %d) appears %d times\n", unique[i].a, unique[i].b, frequency);
    }

    free(unique);
    return 0;
}