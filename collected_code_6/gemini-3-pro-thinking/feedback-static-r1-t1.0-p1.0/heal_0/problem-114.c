#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int a;
    int b;
};

struct TupleFreq {
    struct Tuple tuple;
    size_t freq;
};

int are_tuples_equal(const struct Tuple* t1, const struct Tuple* t2) {
    return (t1->a == t2->a) && (t1->b == t2->b);
}

struct TupleFreq* calculate_frequencies(const struct Tuple* tuples, size_t num_tuples, size_t* out_num_unique) {
    if (!tuples || !out_num_unique) {
        return NULL;
    }

    if (num_tuples == 0) {
        *out_num_unique = 0;
        return NULL;
    }

    struct TupleFreq* frequencies = malloc(num_tuples * sizeof(struct TupleFreq));
    if (!frequencies) {
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < num_tuples; ++i) {
        int found = 0;
        for (size_t j = 0; j < unique_count; ++j) {
            if (are_tuples_equal(&tuples[i], &frequencies[j].tuple)) {
                frequencies[j].freq++;
                found = 1;
                break;
            }
        }
        if (!found) {
            frequencies[unique_count].tuple = tuples[i];
            frequencies[unique_count].freq = 1;
            unique_count++;
        }
    }

    *out_num_unique = unique_count;

    if (unique_count < num_tuples && unique_count > 0) {
        struct TupleFreq* resized = realloc(frequencies, unique_count * sizeof(struct TupleFreq));
        if (resized) {
            frequencies = resized;
        }
    }

    return frequencies;
}

int main(void) {
    struct Tuple input_tuples[] = {
        {1, 2}, {3, 4}, {1, 2}, {5, 6}, {3, 4}, {1, 2}
    };
    size_t num_tuples = sizeof(input_tuples) / sizeof(input_tuples[0]);
    size_t num_unique = 0;

    struct TupleFreq* result = calculate_frequencies(input_tuples, num_tuples, &num_unique);

    if (!result && num_tuples > 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < num_unique; ++i) {
        printf("(%d, %d): %zu\n", result[i].tuple.a, result[i].tuple.b, result[i].freq);
    }

    free(result);

    return EXIT_SUCCESS;
}