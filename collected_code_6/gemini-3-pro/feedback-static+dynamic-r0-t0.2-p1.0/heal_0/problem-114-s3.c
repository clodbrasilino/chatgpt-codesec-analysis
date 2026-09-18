#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple tuple;
    int frequency;
} TupleFrequency;

int compare_tuples(const Tuple *t1, const Tuple *t2) {
    if (t1->size != t2->size) {
        return 0;
    }
    for (size_t i = 0; i < t1->size; i++) {
        if (t1->elements[i] != t2->elements[i]) {
            return 0;
        }
    }
    return 1;
}

TupleFrequency* assign_frequencies(Tuple *tuples, size_t num_tuples, size_t *out_size) {
    if (!tuples || num_tuples == 0 || !out_size) {
        return NULL;
    }

    TupleFrequency *freq_list = malloc(num_tuples * sizeof(TupleFrequency));
    if (!freq_list) {
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < num_tuples; i++) {
        int found = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (compare_tuples(&tuples[i], &freq_list[j].tuple)) {
                freq_list[j].frequency++;
                found = 1;
                break;
            }
        }
        if (!found) {
            freq_list[unique_count].tuple = tuples[i];
            freq_list[unique_count].frequency = 1;
            unique_count++;
        }
    }

    *out_size = unique_count;
    return freq_list;
}

int main(void) {
    int e1[] = {1, 2};
    int e2[] = {3, 4};
    int e3[] = {1, 2};
    int e4[] = {5};

    Tuple tuples[] = {
        {e1, 2},
        {e2, 2},
        {e3, 2},
        {e4, 1}
    };

    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    size_t out_size = 0;

    TupleFrequency *freq_list = assign_frequencies(tuples, num_tuples, &out_size);

    if (freq_list) {
        for (size_t i = 0; i < out_size; i++) {
            printf("Tuple: (");
            for (size_t j = 0; j < freq_list[i].tuple.size; j++) {
                printf("%d%s", freq_list[i].tuple.elements[j], 
                       j < freq_list[i].tuple.size - 1 ? ", " : "");
            }
            printf(") - Frequency: %d\n", freq_list[i].frequency);
        }
        free(freq_list);
    }

    return 0;
}