#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int value;
} Tuple;

int calculate_max_aggregate(Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return 0;
    }

    int max_id = tuples[0].id;
    for (size_t i = 1; i < count; i++) {
        if (tuples[i].id > max_id) {
            max_id = tuples[i].id;
        }
    }

    int *aggregates = (int *)calloc(max_id + 1, sizeof(int));
    if (aggregates == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; i++) {
        aggregates[tuples[i].id] += tuples[i].value;
    }

    int max_aggregate = aggregates[0];
    for (int i = 1; i <= max_id; i++) {
        if (aggregates[i] > max_aggregate) {
            max_aggregate = aggregates[i];
        }
    }

    free(aggregates);
    return max_aggregate;
}

int main() {
    Tuple data[] = {
        {1, 5},
        {2, 9},
        {1, -3},
        {3, 12},
        {2, 7},
        {3, -2}
    };
    size_t count = sizeof(data) / sizeof(data[0]);

    int max_agg = calculate_max_aggregate(data, count);
    printf("%d\n", max_agg);

    return 0;
}