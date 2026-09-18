#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    Tuple tuple;
    int count;
} TupleFrequency;

int compare_ints(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int tuples_equal(Tuple t1, Tuple t2) {
    if (t1.size != t2.size) {
        return 0;
    }
    for (int i = 0; i < t1.size; i++) {
        if (t1.elements[i] != t2.elements[i]) {
            return 0;
        }
    }
    return 1;
}

Tuple normalize_tuple(Tuple t) {
    Tuple normalized;
    normalized.size = t.size;
    normalized.elements = (int *)malloc(t.size * sizeof(int));
    if (!normalized.elements) {
        exit(EXIT_FAILURE);
    }
    memcpy(normalized.elements, t.elements, t.size * sizeof(int));
    qsort(normalized.elements, normalized.size, sizeof(int), compare_ints);
    return normalized;
}

TupleFrequency* extract_frequencies(const Tuple *tuples, int num_tuples, int *out_num_unique) {
    if (!tuples || num_tuples <= 0 || !out_num_unique) {
        return NULL;
    }

    TupleFrequency *freqs = (TupleFrequency *)malloc(num_tuples * sizeof(TupleFrequency));
    if (!freqs) {
        return NULL;
    }

    int unique_count = 0;

    for (int i = 0; i < num_tuples; i++) {
        Tuple normalized = normalize_tuple(tuples[i]);
        int found = 0;

        for (int j = 0; j < unique_count; j++) {
            if (tuples_equal(freqs[j].tuple, normalized)) {
                freqs[j].count++;
                found = 1;
                free(normalized.elements);
                break;
            }
        }

        if (!found) {
            freqs[unique_count].tuple = normalized;
            freqs[unique_count].count = 1;
            unique_count++;
        }
    }

    *out_num_unique = unique_count;
    return freqs;
}

void free_frequencies(TupleFrequency *freqs, int num_unique) {
    if (!freqs) return;
    for (int i = 0; i < num_unique; i++) {
        free(freqs[i].tuple.elements);
    }
    free(freqs);
}

int main(void) {
    int t1_data[] = {1, 2, 3};
    int t2_data[] = {3, 2, 1};
    int t3_data[] = {4, 5};
    int t4_data[] = {1, 2, 3};

    const Tuple tuples[4] = {
        {t1_data, 3},
        {t2_data, 3},
        {t3_data, 2},
        {t4_data, 3}
    };

    int num_unique = 0;
    TupleFrequency *freqs = extract_frequencies(tuples, 4, &num_unique);

    if (freqs) {
        for (int i = 0; i < num_unique; i++) {
            printf("Tuple: (");
            for (int j = 0; j < freqs[i].tuple.size; j++) {
                printf("%d%s", freqs[i].tuple.elements[j], j < freqs[i].tuple.size - 1 ? ", " : "");
            }
            printf(") - Frequency: %d\n", freqs[i].count);
        }
        free_frequencies(freqs, num_unique);
    }

    return 0;
}