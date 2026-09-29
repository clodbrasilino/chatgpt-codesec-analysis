#include <stdio.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple tuple;
    int frequency;
} TupleFrequency;

static int tuple_equal(const Tuple *lhs, const Tuple *rhs) {
    return (lhs->first == rhs->first && lhs->second == rhs->second) ||
           (lhs->first == rhs->second && lhs->second == rhs->first);
}

void extract_tuple_frequencies(const Tuple *tuples, size_t count,
                               TupleFrequency *frequencies, size_t *unique_count) {
    if (unique_count == NULL || frequencies == NULL || tuples == NULL || count == 0) {
        if (unique_count != NULL) {
            *unique_count = 0;
        }
        return;
    }

    size_t unique = 0;

    for (size_t i = 0; i < count; ++i) {
        int found = 0;

        for (size_t j = 0; j < unique; ++j) {
            if (tuple_equal(&tuples[i], &frequencies[j].tuple)) {
                ++frequencies[j].frequency;
                found = 1;
                break;
            }
        }

        if (!found) {
            frequencies[unique].tuple = tuples[i];
            frequencies[unique].frequency = 1;
            ++unique;
        }
    }

    *unique_count = unique;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2},
        {2, 1},
        {3, 4},
        {1, 2},
        {4, 3},
        {5, 6}
    };

    TupleFrequency frequencies[sizeof(tuples) / sizeof(tuples[0])];
    size_t unique_count = 0;

    extract_tuple_frequencies(tuples, sizeof(tuples) / sizeof(tuples[0]),
                              frequencies, &unique_count);

    for (size_t i = 0; i < unique_count; ++i) {
        printf("(%d, %d): %d\n", frequencies[i].tuple.first,
               frequencies[i].tuple.second, frequencies[i].frequency);
    }

    return 0;
}