#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int tuples_to_set(const Tuple *tuples, size_t tuple_count, Tuple **set_out, size_t *set_size) {
    if (set_out == NULL || set_size == NULL) {
        return -1;
    }
    if (tuple_count > 0 && tuples == NULL) {
        return -1;
    }

    *set_out = NULL;
    *set_size = 0;

    if (tuple_count == 0) {
        return 0;
    }

    Tuple *set = malloc(tuple_count * sizeof(Tuple));
    if (set == NULL) {
        return -2;
    }

    size_t set_count = 0;

    for (size_t i = 0; i < tuple_count; i++) {
        int exists = 0;
        for (size_t j = 0; j < set_count; j++) {
            if (set[j].first == tuples[i].first && set[j].second == tuples[i].second) {
                exists = 1;
                break;
            }
        }
        if (!exists) {
            set[set_count] = tuples[i];
            set_count++;
        }
    }

    if (set_count > 0) {
        Tuple *shrunk = realloc(set, set_count * sizeof(Tuple));
        if (shrunk == NULL) {
            free(set);
            return -2;
        }
        set = shrunk;
    } else {
        free(set);
        set = NULL;
    }

    *set_out = set;
    *set_size = set_count;
    return 0;
}

int main(void) {
    Tuple input[] = {
        {1, 2},
        {3, 4},
        {1, 2},
        {5, 6},
        {3, 4}
    };
    size_t input_count = sizeof(input) / sizeof(input[0]);
    Tuple *set = NULL;
    size_t set_count = 0;

    int result = tuples_to_set(input, input_count, &set, &set_count);
    if (result != 0) {
        fprintf(stderr, "Error converting tuples to set\n");
        return 1;
    }

    for (size_t i = 0; i < set_count; i++) {
        printf("(%d, %d)\n", set[i].first, set[i].second);
    }

    free(set);
    return 0;
}