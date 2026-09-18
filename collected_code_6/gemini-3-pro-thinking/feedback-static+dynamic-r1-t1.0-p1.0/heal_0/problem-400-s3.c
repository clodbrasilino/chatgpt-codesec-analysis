#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple tuple;
    size_t count;
} TupleFreq;

TupleFreq* get_tuple_frequencies(const Tuple* input, size_t size, size_t* out_size) {
    if (!input || !out_size) {
        return NULL;
    }

    if (size == 0) {
        *out_size = 0;
        return NULL;
    }

    TupleFreq* frequencies = malloc(size * sizeof(TupleFreq));
    if (!frequencies) {
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < size; ++i) {
        int min_val = input[i].a < input[i].b ? input[i].a : input[i].b;
        int max_val = input[i].a > input[i].b ? input[i].a : input[i].b;

        int found = 0;
        for (size_t j = 0; j < unique_count; ++j) {
            if (frequencies[j].tuple.a == min_val && frequencies[j].tuple.b == max_val) {
                frequencies[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            frequencies[unique_count].tuple.a = min_val;
            frequencies[unique_count].tuple.b = max_val;
            frequencies[unique_count].count = 1;
            unique_count++;
        }
    }

    *out_size = unique_count;

    if (unique_count < size) {
        TupleFreq* temp = realloc(frequencies, unique_count * sizeof(TupleFreq));
        if (temp) {
            frequencies = temp;
        }
    }

    return frequencies;
}

int main(void) {
    Tuple input[] = {
        {1, 2},
        {2, 1},
        {3, 4},
        {1, 2},
        {4, 3},
        {5, 6}
    };
    
    size_t size = sizeof(input) / sizeof(input[0]);
    size_t out_size = 0;

    TupleFreq* frequencies = get_tuple_frequencies(input, size, &out_size);
    if (!frequencies && size > 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < out_size; ++i) {
        printf("(%d, %d): %zu\n", frequencies[i].tuple.a, frequencies[i].tuple.b, frequencies[i].count);
    }

    free(frequencies);
    
    return EXIT_SUCCESS;
}