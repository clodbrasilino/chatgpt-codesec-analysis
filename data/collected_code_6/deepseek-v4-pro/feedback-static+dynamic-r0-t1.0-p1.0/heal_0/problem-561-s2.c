#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
    int paired_first;
    int paired_second;
} Tuple;

void assign_pairs(Tuple *tuples, int count) {
    if (tuples == NULL || count <= 0) {
        return;
    }

    for (int i = 0; i < count; i++) {
        int pair_index = (i + 1) % count;
        tuples[i].paired_first = tuples[pair_index].first;
        tuples[i].paired_second = tuples[pair_index].second;
    }
}

int main(void) {
    int count = 4;
    Tuple *tuples = malloc((size_t)count * sizeof(Tuple));
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    tuples[0].first = 1;
    tuples[0].second = 2;
    tuples[0].paired_first = 0;
    tuples[0].paired_second = 0;
    tuples[1].first = 3;
    tuples[1].second = 4;
    tuples[1].paired_first = 0;
    tuples[1].paired_second = 0;
    tuples[2].first = 5;
    tuples[2].second = 6;
    tuples[2].paired_first = 0;
    tuples[2].paired_second = 0;
    tuples[3].first = 7;
    tuples[3].second = 8;
    tuples[3].paired_first = 0;
    tuples[3].paired_second = 0;

    assign_pairs(tuples, count);

    for (int i = 0; i < count; i++) {
        printf("Tuple %d: (%d, %d) -> paired with (%d, %d)\n",
               i, tuples[i].first, tuples[i].second,
               tuples[i].paired_first, tuples[i].paired_second);
    }

    free(tuples);
    tuples = NULL;

    return 0;
}