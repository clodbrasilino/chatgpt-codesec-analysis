#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple tuple;
    int frequency;
} TupleFrequency;

int compare_ints(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

bool are_tuples_equal_unordered(const Tuple *t1, const Tuple *t2) {
    if (t1->size != t2->size) {
        return false;
    }

    int *sorted1 = malloc(t1->size * sizeof(int));
    if (!sorted1) return false;
    
    int *sorted2 = malloc(t2->size * sizeof(int));
    if (!sorted2) {
        free(sorted1);
        return false;
    }

    for (size_t i = 0; i < t1->size; ++i) {
        sorted1[i] = t1->elements[i];
        sorted2[i] = t2->elements[i];
    }

    qsort(sorted1, t1->size, sizeof(int), compare_ints);
    qsort(sorted2, t2->size, sizeof(int), compare_ints);

    bool is_match = true;
    for (size_t i = 0; i < t1->size; ++i) {
        if (sorted1[i] != sorted2[i]) {
            is_match = false;
            break;
        }
    }

    free(sorted1);
    free(sorted2);

    return is_match;
}

TupleFrequency* extract_tuple_frequencies(const Tuple *tuples, size_t num_tuples, size_t *out_num_unique) {
    if (!tuples || num_tuples == 0 || !out_num_unique) {
        if (out_num_unique) *out_num_unique = 0;
        return NULL;
    }

    TupleFrequency *frequencies = malloc(num_tuples * sizeof(TupleFrequency));
    if (!frequencies) {
        *out_num_unique = 0;
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < num_tuples; ++i) {
        bool found = false;
        for (size_t j = 0; j < unique_count; ++j) {
            if (are_tuples_equal_unordered(&tuples[i], &frequencies[j].tuple)) {
                frequencies[j].frequency++;
                found = true;
                break;
            }
        }

        if (!found) {
            frequencies[unique_count].tuple = tuples[i];
            frequencies[unique_count].frequency = 1;
            unique_count++;
        }
    }

    *out_num_unique = unique_count;
    return frequencies;
}

int main(void) {
    int t1_data[] = {1, 2, 3};
    int t2_data[] = {3, 2, 1};
    int t3_data[] = {4, 5};
    int t4_data[] = {1, 2, 3};
    int t5_data[] = {5, 4};

    Tuple tuples[] = {
        {t1_data, 3},
        {t2_data, 3},
        {t3_data, 2},
        {t4_data, 3},
        {t5_data, 2}
    };

    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    size_t num_unique = 0;

    TupleFrequency *frequencies = extract_tuple_frequencies(tuples, num_tuples, &num_unique);

    if (frequencies) {
        for (size_t i = 0; i < num_unique; ++i) {
            printf("Tuple { ");
            for (size_t j = 0; j < frequencies[i].tuple.size; ++j) {
                printf("%d ", frequencies[i].tuple.elements[j]);
            }
            printf("} Frequency: %d\n", frequencies[i].frequency);
        }
        free(frequencies);
    }

    return 0;
}