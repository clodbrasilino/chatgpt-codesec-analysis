#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Tuple;

typedef struct {
    Tuple tuple;
    int count;
} TupleFreq;

bool is_same_tuple(Tuple t1, Tuple t2) {
    return (t1.x == t2.x && t1.y == t2.y) || (t1.x == t2.y && t1.y == t2.x);
}

TupleFreq* extract_frequencies(const Tuple* tuples, size_t num_tuples, size_t* out_num_unique) {
    if (!tuples || !out_num_unique || num_tuples == 0) {
        if (out_num_unique) {
            *out_num_unique = 0;
        }
        return NULL;
    }

    TupleFreq* freqs = (TupleFreq*)malloc(num_tuples * sizeof(TupleFreq));
    if (!freqs) {
        *out_num_unique = 0;
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < num_tuples; ++i) {
        bool found = false;
        for (size_t j = 0; j < unique_count; ++j) {
            if (is_same_tuple(tuples[i], freqs[j].tuple)) {
                freqs[j].count++;
                found = true;
                break;
            }
        }
        if (!found) {
            freqs[unique_count].tuple = tuples[i];
            freqs[unique_count].count = 1;
            unique_count++;
        }
    }

    *out_num_unique = unique_count;
    
    TupleFreq* resized_freqs = (TupleFreq*)realloc(freqs, unique_count * sizeof(TupleFreq));
    if (resized_freqs) {
        freqs = resized_freqs;
    }

    return freqs;
}

int main() {
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {2, 1},
        {5, 6},
        {3, 4},
        {4, 3}
    };
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    size_t num_unique = 0;

    TupleFreq* freqs = extract_frequencies(tuples, num_tuples, &num_unique);

    if (freqs) {
        for (size_t i = 0; i < num_unique; ++i) {
            printf("(%d, %d): %d\n", freqs[i].tuple.x, freqs[i].tuple.y, freqs[i].count);
        }
        free(freqs);
    } else {
        printf("Failed to extract frequencies or empty input.\n");
    }

    return 0;
}