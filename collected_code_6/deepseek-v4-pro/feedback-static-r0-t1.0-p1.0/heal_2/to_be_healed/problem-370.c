#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    float value;
    char *label;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    
    if (tuple_a->value < tuple_b->value) return -1;
    if (tuple_a->value > tuple_b->value) return 1;
    return 0;
}

void sort_tuples_by_float(Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return;
    }
    
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
}

void print_tuples(const Tuple *tuples, size_t count) {
    size_t i;
    for (i = 0; i < count; i++) {
        printf("ID: %d, Value: %.2f, Label: %s\n", 
               tuples[i].id, tuples[i].value, tuples[i].label);
    }
}

static char* safe_strdup(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len >= SIZE_MAX) {
        return NULL;
    }
    
    char *result = malloc(len + 1);
    if (result != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, str, len + 1);
    }
    
    return result;
}

void free_tuples(Tuple *tuples, size_t count) {
    size_t i;
    for (i = 0; i < count; i++) {
        free(tuples[i].label);
    }
    free(tuples);
}

int main(void) {
    Tuple *tuples = malloc(5 * sizeof(Tuple));
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    tuples[0].id = 1;
    tuples[0].value = 3.14f;
    tuples[0].label = safe_strdup("pi");
    
    tuples[1].id = 2;
    tuples[1].value = 1.41f;
    tuples[1].label = safe_strdup("sqrt2");
    
    tuples[2].id = 3;
    tuples[2].value = 2.72f;
    tuples[2].label = safe_strdup("e");
    
    tuples[3].id = 4;
    tuples[3].value = 0.58f;
    tuples[3].label = safe_strdup("gamma");
    
    tuples[4].id = 5;
    tuples[4].value = 1.62f;
    tuples[4].label = safe_strdup("phi");
    
    size_t tuple_count = 5;
    
    int allocation_failed = 0;
    size_t i;
    for (i = 0; i < tuple_count; i++) {
        if (tuples[i].label == NULL) {
            allocation_failed = 1;
            break;
        }
    }
    
    if (allocation_failed) {
        for (i = 0; i < tuple_count; i++) {
            free(tuples[i].label);
        }
        free(tuples);
        fprintf(stderr, "Memory allocation failed for labels\n");
        return 1;
    }
    
    printf("Before sorting:\n");
    print_tuples(tuples, tuple_count);
    
    sort_tuples_by_float(tuples, tuple_count);
    
    printf("\nAfter sorting by float value:\n");
    print_tuples(tuples, tuple_count);
    
    free_tuples(tuples, tuple_count);
    
    return 0;
}