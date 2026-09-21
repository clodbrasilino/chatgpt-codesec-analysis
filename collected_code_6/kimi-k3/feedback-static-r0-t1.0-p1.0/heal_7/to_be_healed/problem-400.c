#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple tuple;
    size_t count;
} TupleFreq;

static int compare_ints(const void *a, const void *b)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

static int tuples_equal(const Tuple *a, const Tuple *b)
{
    if (a->size != b->size) {
        return 0;
    }
    if (a->size > 0 && (a->elements == NULL || b->elements == NULL)) {
        return 0;
    }
    for (size_t i = 0; i < a->size; i++) {
        if (a->elements[i] != b->elements[i]) {
            return 0;
        }
    }
    return 1;
}

static void normalize_tuple(Tuple *t)
{
    if (t->size > 0 && t->elements != NULL) {
        qsort(t->elements, t->size, sizeof(int), compare_ints);
    }
}

static int safe_multiply_size(size_t a, size_t b, size_t *result)
{
    if (result == NULL) {
        return 0;
    }
    if (a == 0 || b == 0) {
        *result = 0;
        return 1;
    }
    if (a > SIZE_MAX / b) {
        return 0;
    }
    *result = a * b;
    return 1;
}

TupleFreq *get_tuple_frequencies(Tuple *tuples, size_t num_tuples, size_t *result_size)
{
    size_t alloc_size;
    size_t copy_size;

    if (tuples == NULL || result_size == NULL || num_tuples == 0) {
        return NULL;
    }

    if (!safe_multiply_size(num_tuples, sizeof(Tuple), &alloc_size)) {
        return NULL;
    }

    Tuple *normalized = malloc(alloc_size);
    if (normalized == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < num_tuples; i++) {
        normalized[i].size = tuples[i].size;
        
        if (tuples[i].size == 0) {
            normalized[i].elements = NULL;
            continue;
        }
        
        if (tuples[i].elements == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(normalized[j].elements);
            }
            free(normalized);
            return NULL;
        }
        
        if (!safe_multiply_size(tuples[i].size, sizeof(int), &copy_size)) {
            for (size_t j = 0; j < i; j++) {
                free(normalized[j].elements);
            }
            free(normalized);
            return NULL;
        }
        
        normalized[i].elements = malloc(copy_size);
        if (normalized[i].elements == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(normalized[j].elements);
            }
            free(normalized);
            return NULL;
        }
        
        if (copy_size > 0 && normalized[i].elements != NULL && tuples[i].elements != NULL) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(normalized[i].elements, tuples[i].elements, copy_size);
        }
        normalize_tuple(&normalized[i]);
    }

    if (!safe_multiply_size(num_tuples, sizeof(TupleFreq), &alloc_size)) {
        for (size_t i = 0; i < num_tuples; i++) {
            free(normalized[i].elements);
        }
        free(normalized);
        return NULL;
    }

    TupleFreq *result = malloc(alloc_size);
    if (result == NULL) {
        for (size_t i = 0; i < num_tuples; i++) {
            free(normalized[i].elements);
        }
        free(normalized);
        return NULL;
    }

    size_t unique_count = 0;
    for (size_t i = 0; i < num_tuples; i++) {
        int found = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (tuples_equal(&normalized[i], &result[j].tuple)) {
                result[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            result[unique_count].tuple.size = normalized[i].size;
            
            if (normalized[i].size == 0) {
                result[unique_count].tuple.elements = NULL;
            } else {
                if (!safe_multiply_size(normalized[i].size, sizeof(int), &copy_size)) {
                    for (size_t k = 0; k < unique_count; k++) {
                        free(result[k].tuple.elements);
                    }
                    free(result);
                    for (size_t k = 0; k < num_tuples; k++) {
                        free(normalized[k].elements);
                    }
                    free(normalized);
                    return NULL;
                }
                
                result[unique_count].tuple.elements = malloc(copy_size);
                if (result[unique_count].tuple.elements == NULL) {
                    for (size_t k = 0; k < unique_count; k++) {
                        free(result[k].tuple.elements);
                    }
                    free(result);
                    for (size_t k = 0; k < num_tuples; k++) {
                        free(normalized[k].elements);
                    }
                    free(normalized);
                    return NULL;
                }
                
                if (copy_size > 0 && result[unique_count].tuple.elements != NULL && normalized[i].elements != NULL) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result[unique_count].tuple.elements, normalized[i].elements, copy_size);
                }
            }
            result[unique_count].count = 1;
            unique_count++;
        }
    }

    for (size_t i = 0; i < num_tuples; i++) {
        free(normalized[i].elements);
    }
    free(normalized);

    *result_size = unique_count;
    return result;
}

void free_tuple_frequencies(TupleFreq *freqs, size_t size)
{
    if (freqs == NULL) {
        return;
    }
    for (size_t i = 0; i < size; i++) {
        free(freqs[i].tuple.elements);
    }
    free(freqs);
}

int main(void)
{
    int t1[] = {1, 2, 3};
    int t2[] = {3, 2, 1};
    int t3[] = {4, 5};
    int t4[] = {2, 1, 3};
    int t5[] = {5, 4};

    Tuple tuples[] = {
        {t1, 3},
        {t2, 3},
        {t3, 2},
        {t4, 3},
        {t5, 2}
    };

    size_t result_size = 0;
    TupleFreq *freqs = get_tuple_frequencies(tuples, 5, &result_size);
    
    if (freqs == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Unique tuple frequencies (order irrespective):\n");
    for (size_t i = 0; i < result_size; i++) {
        printf("Tuple [");
        for (size_t j = 0; j < freqs[i].tuple.size; j++) {
            printf("%d", freqs[i].tuple.elements[j]);
            if (j < freqs[i].tuple.size - 1) {
                printf(", ");
            }
        }
        printf("] : %zu\n", freqs[i].count);
    }

    free_tuple_frequencies(freqs, result_size);
    return EXIT_SUCCESS;
}