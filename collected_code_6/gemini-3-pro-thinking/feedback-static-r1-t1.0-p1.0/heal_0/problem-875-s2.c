#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

int get_min_tuple_difference(const Tuple *tuples, size_t count, unsigned int *min_diff);

int get_min_tuple_difference(const Tuple *tuples, size_t count, unsigned int *min_diff) {
    unsigned int current_min = UINT_MAX;
    size_t i;
    long long diff;
    unsigned int abs_diff;

    if (tuples == NULL || min_diff == NULL || count == 0) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        diff = (long long)tuples[i].first - (long long)tuples[i].second;
        abs_diff = (unsigned int)llabs(diff);
        if (abs_diff < current_min) {
            current_min = abs_diff;
        }
    }

    *min_diff = current_min;
    return 0;
}

int main(void) {
    size_t count = 4;
    Tuple *tuples = NULL;
    unsigned int min_diff = 0;

    tuples = (Tuple *)malloc(count * sizeof(Tuple));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    tuples[0].first = 15;
    tuples[0].second = 10;
    
    tuples[1].first = 100;
    tuples[1].second = 200;
    
    tuples[2].first = -5;
    tuples[2].second = 5;

    tuples[3].first = 42;
    tuples[3].second = 44;

    if (get_min_tuple_difference(tuples, count, &min_diff) == 0) {
        printf("%u\n", min_diff);
    } else {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}