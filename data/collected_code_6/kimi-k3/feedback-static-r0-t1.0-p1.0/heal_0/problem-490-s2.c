#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

bool find_symmetric_pairs(const Tuple *tuples, size_t size, Tuple *result, size_t *result_count) {
    if (tuples == NULL || result == NULL || result_count == NULL) {
        return false;
    }
    
    *result_count = 0;
    
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (tuples[i].first == tuples[j].second && 
                tuples[i].second == tuples[j].first) {
                if (*result_count >= size / 2) {
                    return false;
                }
                result[*result_count] = tuples[i];
                (*result_count)++;
                break;
            }
        }
    }
    
    return true;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2}, {3, 4}, {2, 1}, {5, 6}, {4, 3}, {7, 8}
    };
    size_t size = sizeof(tuples) / sizeof(tuples[0]);
    size_t max_pairs = size / 2;
    size_t result_count = 0;
    
    Tuple *result = malloc(max_pairs * sizeof(Tuple));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    if (!find_symmetric_pairs(tuples, size, result, &result_count)) {
        fprintf(stderr, "Error finding symmetric pairs\n");
        free(result);
        return EXIT_FAILURE;
    }
    
    printf("Symmetric pairs found: %zu\n", result_count);
    for (size_t i = 0; i < result_count; i++) {
        printf("(%d, %d)\n", result[i].first, result[i].second);
    }
    
    free(result);
    return EXIT_SUCCESS;
}