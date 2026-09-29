#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    size_t len;
} Tuple;

int has_all_k_elements(Tuple *tuples, size_t tuple_count, size_t k) {
    size_t i;
    size_t j;
    int found;
    char *element;
    
    if (tuples == NULL || k == 0) {
        return 0;
    }
    
    for (i = 0; i < tuple_count; i++) {
        if (tuples[i].data == NULL) {
            continue;
        }
        
        element = tuples[i].data;
        
        if (tuples[i].len != k) {
            return 0;
        }
        
        found = 0;
        for (j = 0; j < k; j++) {
            if (element[j] != '\0') {
                found = 1;
            } else {
                found = 0;
                break;
            }
        }
        
        if (!found) {
            return 0;
        }
    }
    
    return 1;
}

int main(void) {
    Tuple tuples[3];
    size_t k = 3;
    int result;
    
    tuples[0].data = malloc(4);
    tuples[1].data = malloc(4);
    tuples[2].data = malloc(4);
    
    if (tuples[0].data == NULL || tuples[1].data == NULL || tuples[2].data == NULL) {
        free(tuples[0].data);
        free(tuples[1].data);
        free(tuples[2].data);
        return 1;
    }
    
    snprintf(tuples[0].data, 4, "abc");
    tuples[0].len = 3;
    
    snprintf(tuples[1].data, 4, "def");
    tuples[1].len = 3;
    
    snprintf(tuples[2].data, 4, "ghi");
    tuples[2].len = 3;
    
    result = has_all_k_elements(tuples, 3, k);
    
    if (result) {
        printf("All tuples have %zu elements\n", k);
    } else {
        printf("Not all tuples have %zu elements\n", k);
    }
    
    free(tuples[0].data);
    free(tuples[1].data);
    free(tuples[2].data);
    
    return 0;
}