#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TUPLE_SIZE 10

typedef struct {
    int elements[MAX_TUPLE_SIZE];
    int size;
} Tuple;

typedef struct {
    Tuple tuple;
    int count;
} TupleFrequency;

int compare_ints(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

bool are_tuples_equal_unordered(const Tuple *t1, const Tuple *t2) {
    if (t1->size != t2->size || t1->size < 0 || t1->size > MAX_TUPLE_SIZE) {
        return false;
    }
    
    int arr1[MAX_TUPLE_SIZE];
    int arr2[MAX_TUPLE_SIZE];
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(arr1, t1->elements, t1->size * sizeof(int));
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(arr2, t2->elements, t2->size * sizeof(int));
    
    qsort(arr1, t1->size, sizeof(int), compare_ints);
    qsort(arr2, t2->size, sizeof(int), compare_ints);
    
    bool is_equal = (memcmp(arr1, arr2, t1->size * sizeof(int)) == 0);
    
    return is_equal;
}

TupleFrequency* extract_frequencies(const Tuple* tuples, int num_tuples, int* out_count) {
    if (!tuples || num_tuples < 0 || !out_count) {
        return NULL;
    }

    if (num_tuples == 0) {
        *out_count = 0;
        return NULL;
    }

    TupleFrequency* frequencies = malloc(num_tuples * sizeof(TupleFrequency));
    if (!frequencies) {
        return NULL;
    }

    int unique_count = 0;

    for (int i = 0; i < num_tuples; i++) {
        bool found = false;
        for (int j = 0; j < unique_count; j++) {
            if (are_tuples_equal_unordered(&tuples[i], &frequencies[j].tuple)) {
                frequencies[j].count++;
                found = true;
                break;
            }
        }
        if (!found) {
            frequencies[unique_count].tuple = tuples[i];
            frequencies[unique_count].count = 1;
            unique_count++;
        }
    }

    *out_count = unique_count;
    
    TupleFrequency* final_frequencies = realloc(frequencies, unique_count * sizeof(TupleFrequency));
    if (unique_count > 0 && !final_frequencies) {
        free(frequencies);
        return NULL;
    }

    return final_frequencies ? final_frequencies : frequencies;
}

int main(void) {
    Tuple tuples[] = {
        {{1, 2, 3}, 3},
        {{3, 1, 2}, 3},
        {{4, 5}, 2},
        {{2, 1, 3}, 3},
        {{5, 4}, 2},
        {{1, 2}, 2}
    };
    int num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    int unique_count = 0;

    TupleFrequency* frequencies = extract_frequencies(tuples, num_tuples, &unique_count);

    if (frequencies) {
        for (int i = 0; i < unique_count; i++) {
            printf("Tuple: (");
            for (int j = 0; j < frequencies[i].tuple.size; j++) {
                printf("%d%s", frequencies[i].tuple.elements[j], 
                       j < frequencies[i].tuple.size - 1 ? ", " : "");
            }
            printf(") - Frequency: %d\n", frequencies[i].count);
        }
        free(frequencies);
    } else {
        printf("Failed to extract frequencies.\n");
    }

    return 0;
}