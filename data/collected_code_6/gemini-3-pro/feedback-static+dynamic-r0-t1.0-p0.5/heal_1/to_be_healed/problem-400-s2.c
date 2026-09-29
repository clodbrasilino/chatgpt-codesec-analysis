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
    
    int *sorted_t1 = malloc(t1->size * sizeof(int));
    if (!sorted_t1) return false;
    
    int *sorted_t2 = malloc(t2->size * sizeof(int));
    if (!sorted_t2) {
        free(sorted_t1);
        return false;
    }
    
    for (size_t i = 0; i < t1->size; i++) {
        sorted_t1[i] = t1->elements[i];
        sorted_t2[i] = t2->elements[i];
    }
    
    qsort(sorted_t1, t1->size, sizeof(int), compare_ints);
    qsort(sorted_t2, t2->size, sizeof(int), compare_ints);
    
    bool equal = true;
    for (size_t i = 0; i < t1->size; i++) {
        if (sorted_t1[i] != sorted_t2[i]) {
            equal = false;
            break;
        }
    }
    
    free(sorted_t1);
    free(sorted_t2);
    
    /* Possible weaknesses found:
     * Flawfinder equal: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    return equal;
}

TupleFrequency* extract_tuple_frequencies(const Tuple *tuples, size_t num_tuples, size_t *out_count) {
    if (!tuples || !out_count) return NULL;
    
    TupleFrequency *frequencies = malloc(num_tuples * sizeof(TupleFrequency));
    if (!frequencies) return NULL;
    
    size_t unique_count = 0;
    
    for (size_t i = 0; i < num_tuples; i++) {
        bool found = false;
        for (size_t j = 0; j < unique_count; j++) {
            if (are_tuples_equal(&tuples[i], &frequencies[j].tuple)) {
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
    
    *out_count = unique_count;
    return frequencies;
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
    size_t unique_count = 0;
    
    TupleFrequency *frequencies = extract_tuple_frequencies(tuples, num_tuples, &unique_count);
    
    if (frequencies) {
        for (size_t i = 0; i < unique_count; i++) {
            printf("Tuple { ");
            for (size_t j = 0; j < frequencies[i].tuple.size; j++) {
                printf("%d ", frequencies[i].tuple.elements[j]);
            }
            printf("} Frequency: %d\n", frequencies[i].frequency);
        }
        free(frequencies);
    }
    
    return 0;
}