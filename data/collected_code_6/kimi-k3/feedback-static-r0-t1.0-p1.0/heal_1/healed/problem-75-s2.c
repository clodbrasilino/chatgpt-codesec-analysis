#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

int all_divisible(const Tuple *tuple, int k) {
    if (tuple == NULL || tuple->elements == NULL || k == 0) {
        return 0;
    }
    
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i] % k != 0) {
            return 0;
        }
    }
    
    return 1;
}

Tuple *find_divisible_tuples(const Tuple *tuples, size_t count, int k, size_t *result_count) {
    if (tuples == NULL || result_count == NULL || k == 0) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }
    
    size_t valid_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (all_divisible(&tuples[i], k)) {
            valid_count++;
        }
    }
    
    if (valid_count == 0) {
        *result_count = 0;
        return NULL;
    }
    
    Tuple *result = malloc(valid_count * sizeof(Tuple));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }
    
    for (size_t i = 0; i < valid_count; i++) {
        result[i].elements = NULL;
        result[i].size = 0;
    }
    
    size_t j = 0;
    for (size_t i = 0; i < count && j < valid_count; i++) {
        if (all_divisible(&tuples[i], k)) {
            result[j].size = tuples[i].size;
            result[j].elements = malloc(tuples[i].size * sizeof(int));
            
            if (result[j].elements == NULL) {
                for (size_t l = 0; l < j; l++) {
                    free(result[l].elements);
                }
                free(result);
                *result_count = 0;
                return NULL;
            }
            
            for (size_t m = 0; m < tuples[i].size; m++) {
                result[j].elements[m] = tuples[i].elements[m];
            }
            j++;
        }
    }
    
    *result_count = valid_count;
    return result;
}

void free_tuples(Tuple *tuples, size_t count) {
    if (tuples == NULL) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        free(tuples[i].elements);
    }
    free(tuples);
}

int main(void) {
    Tuple tuples[4];
    int data1[] = {6, 12, 18};
    int data2[] = {4, 8, 16};
    int data3[] = {5, 10, 15};
    int data4[] = {3, 6, 9};
    size_t result_count;
    int k = 3;
    
    tuples[0].elements = data1;
    tuples[0].size = 3;
    tuples[1].elements = data2;
    tuples[1].size = 3;
    tuples[2].elements = data3;
    tuples[2].size = 3;
    tuples[3].elements = data4;
    tuples[3].size = 3;
    
    Tuple *result = find_divisible_tuples(tuples, 4, k, &result_count);
    
    if (result != NULL) {
        printf("Tuples with all elements divisible by %d:\n", k);
        for (size_t i = 0; i < result_count; i++) {
            printf("(");
            for (size_t j = 0; j < result[i].size; j++) {
                printf("%d", result[i].elements[j]);
                if (j < result[i].size - 1) {
                    printf(", ");
                }
            }
            printf(")\n");
        }
        free_tuples(result, result_count);
    } else {
        printf("No tuples found with all elements divisible by %d\n", k);
    }
    
    return 0;
}