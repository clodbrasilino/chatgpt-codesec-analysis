#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Pair;

int pair_cmp(const void *x, const void *y) {
    return ((Pair *)x)->a - ((Pair *)y)->a;
}

void assign_pairs(Pair *tuples, int n) {
    if (n == 0) return;

    qsort(tuples, n, sizeof(Pair), pair_cmp);

    for (int i = 1; i < n; ++i) {
        tuples[i-1].b = tuples[i].a;
    }
    tuples[n-1].b = -1; // Indicate no next pair
}

int main() {
    Pair tuples[] = {{5, 0}, {2, 0}, {8, 0}, {20, 0}, {50, 0}};
    int n = sizeof(tuples) / sizeof(tuples[0]);

    assign_pairs(tuples, n);

    for (int i = 0; i < n; ++i) {
        printf("(%d, %d)\n", tuples[i].a, tuples[i].b);
    }

    return 0;
}