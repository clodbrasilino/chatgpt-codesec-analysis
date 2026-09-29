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

bool are_tuples_equal(const Tuple *t1, const Tuple *t2) {
    if (t1->size != t2->size) return false;
    
    int *sorted1 = malloc(t1->size * sizeof(int));
    if (!sorted1) return false;
    
    int *sorted2 = malloc(t2->size * sizeof(int));
    if (!sorted2) {
        free(sorted1);
        return false;
    }
    
    for (size_t i = 0; i < t1->size; i++) {
        sorted1[i] = t1->elements[i];
        sorted2[i] = t2->elements[i];
    }
    
    qsort(sorted1, t1->size, sizeof(int), compare_ints);
    qsort(sorted2, t2->size, sizeof(int), compare_ints);
    
    bool equal = true;
    for (size_t i = 0; i < t1->size; i++) {
        if (sorted1[i] != sorted2[i]) {
            equal = false;
            break;
        }
    }
    
    free(sorted1);
    free(sorted2);
    /* Possible weaknesses found:
     * Flawfinder equal: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    return equal;
}

TupleFrequency* extract_frequencies(const Tuple *tuples, size_t num_tuples, size_t *out_num_unique) {
    if (!tuples || num_tuples == 0 || !out_num_unique) {
        if (out_num_unique) *out_num_unique = 0;
        return NULL;
    }
    
    TupleFrequency *freqs = malloc(num_tuples * sizeof(TupleFrequency));
    if (!freqs) {
        *out_num_unique = 0;
        return NULL;
    }
    
    size_t unique_count = 0;
    
    for (size_t i = 0; i < num_tuples; i++) {
        bool found = false;
        for (size_t j = 0; j < unique_count; j++) {
            if (are_tuples_equal(&tuples[i], &freqs[j].tuple)) {
                freqs[j].frequency++;
                found = true;
                break;
            }
        }
        
        if (!found) {
            freqs[unique_count].tuple.size = tuples[i].size;
            freqs[unique_count].tuple.elements = malloc(tuples[i].size * sizeof(int));
            if (!freqs[unique_count].tuple.elements) {
                for (size_t k = 0; k < unique_count; k++) {
                    free(freqs[k].tuple.elements);
                }
                free(freqs);
                *out_num_unique = 0;
                return NULL;
            }
            for (size_t k = 0; k < tuples[i].size; k++) {
                freqs[unique_count].tuple.elements[k] = tuples[i].elements[k];
            }
            freqs[unique_count].frequency = 1;
            unique_count++;
        }
    }
    
    *out_num_unique = unique_count;
    return freqs;
}

void free_frequencies(TupleFrequency *freqs, size_t num_unique) {
    if (!freqs) return;
    for (size_t i = 0; i < num_unique; i++) {
        free(freqs[i].tuple.elements);
    }
    free(freqs);
}

int main(void) {
    int t1_data[] = {1, 2, 3};
    int t2_data[] = {3, 2, 1};
    int t3_data[] = {4, 5};
    int t4_data[] = {1, 2, 3};
    
    Tuple tuples[] = {
        {t1_data, 3},
        {t2_data, 3},
        {t3_data, 2},
        {t4_data, 3}
    };
    
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    size_t num_unique = 0;
    
    TupleFrequency *freqs = extract_frequencies(tuples, num_tuples, &num_unique);
    
    if (freqs) {
        for (size_t i = 0; i < num_unique; i++) {
            printf("Tuple { ");
            for (size_t j = 0; j < freqs[i].tuple.size; j++) {
                printf("%d ", freqs[i].tuple.elements[j]);
            }
            printf("} Frequency: %d\n", freqs[i].frequency);
        }
        free_frequencies(freqs, num_unique);
    }
    
    return 0;
}