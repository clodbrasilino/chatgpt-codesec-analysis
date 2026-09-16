#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    Pair *pairs;
    int count;
} Tuple;

int find_pair_index(Tuple *tuple, int first, int second) {
    for (int i = 0; i < tuple->count; i++) {
        if (tuple->pairs[i].first == first && tuple->pairs[i].second == second) {
            return i;
        }
    }
    return -1;
}

void assign_pair_elements(Tuple *tuple) {
    if (tuple == NULL || tuple->pairs == NULL || tuple->count <= 0) {
        return;
    }

    int *assigned = (int *)calloc(tuple->count, sizeof(int));
    if (assigned == NULL) {
        return;
    }

    for (int i = 0; i < tuple->count; i++) {
        if (assigned[i]) {
            continue;
        }

        int first = tuple->pairs[i].first;
        int second = tuple->pairs[i].second;

        int match_index = find_pair_index(tuple, second, first);
        if (match_index == -1) {
            assigned[i] = 1;
            continue;
        }

        if (i == match_index) {
            assigned[i] = 1;
            continue;
        }

        if (assigned[match_index]) {
            assigned[i] = 1;
            continue;
        }

        int temp_first = tuple->pairs[i].first;
        int temp_second = tuple->pairs[i].second;
        tuple->pairs[i].first = tuple->pairs[match_index].first;
        tuple->pairs[i].second = tuple->pairs[match_index].second;
        tuple->pairs[match_index].first = temp_first;
        tuple->pairs[match_index].second = temp_second;

        assigned[i] = 1;
        assigned[match_index] = 1;
    }

    free(assigned);
}

int main(void) {
    Pair pairs[] = {
        {1, 2},
        {3, 4},
        {2, 1},
        {5, 6},
        {4, 3}
    };
    int count = sizeof(pairs) / sizeof(pairs[0]);

    Tuple tuple;
    tuple.pairs = (Pair *)malloc(count * sizeof(Pair));
    if (tuple.pairs == NULL) {
        return 1;
    }
    tuple.count = count;

    memcpy(tuple.pairs, pairs, count * sizeof(Pair));

    assign_pair_elements(&tuple);

    for (int i = 0; i < tuple.count; i++) {
        printf("(%d, %d)\n", tuple.pairs[i].first, tuple.pairs[i].second);
    }

    free(tuple.pairs);
    tuple.pairs = NULL;
    tuple.count = 0;

    return 0;
}