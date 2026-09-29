#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

void assign_pairs(Pair *tuples, int size) {
    if (tuples == NULL || size < 2) {
        return;
    }

    int last_first = tuples[size - 1].first;
    int last_second = tuples[size - 1].second;

    for (int i = size - 1; i > 0; i--) {
        tuples[i].first = tuples[i - 1].first;
        tuples[i].second = tuples[i - 1].second;
    }

    tuples[0].first = last_first;
    tuples[0].second = last_second;
}

int main(void) {
    Pair *tuples = (Pair *)malloc(4 * sizeof(Pair));
    if (tuples == NULL) {
        return 1;
    }

    tuples[0].first = 1;
    tuples[0].second = 10;
    tuples[1].first = 2;
    tuples[1].second = 20;
    tuples[2].first = 3;
    tuples[2].second = 30;
    tuples[3].first = 4;
    tuples[3].second = 40;

    assign_pairs(tuples, 4);

    for (int i = 0; i < 4; i++) {
        printf("%d: %d %d\n", i, tuples[i].first, tuples[i].second);
    }

    free(tuples);
    tuples = NULL;

    return 0;
}