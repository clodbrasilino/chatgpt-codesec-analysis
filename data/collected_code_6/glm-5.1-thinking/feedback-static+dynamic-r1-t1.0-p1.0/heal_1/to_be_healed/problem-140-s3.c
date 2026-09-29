#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

int tuple_compare(const void *a, const void *b) {
    const Tuple *ta = a;
    const Tuple *tb = b;
    if (ta->first < tb->first) return -1;
    if (ta->first > tb->first) return 1;
    if (ta->second < tb->second) return -1;
    if (ta->second > tb->second) return 1;
    return 0;
}

Tuple* extract_singly(const Tuple* arr, size_t n, size_t* out_n) {
    if (arr == NULL || out_n == NULL) {
        return NULL;
    }
    
    *out_n = 0;
    
    if (n == 0) {
        return NULL;
    }
    
    Tuple* sorted = malloc(n * sizeof(Tuple));
    if (sorted == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted, arr, n * sizeof(Tuple));
    qsort(sorted, n, sizeof(Tuple), tuple_compare);
    
    Tuple* result = malloc(n * sizeof(Tuple));
    if (result == NULL) {
        free(sorted);
        return NULL;
    }
    
    size_t i = 0;
    while (i < n) {
        size_t count = 1;
        while (i + count < n && tuple_compare(&sorted[i], &sorted[i + count]) == 0) {
            count++;
        }
        if (count == 1) {
            result[*out_n] = sorted[i];
            (*out_n)++;
        }
        i += count;
    }
    
    free(sorted);
    
    if (*out_n == 0) {
        free(result);
        return NULL;
    }
    
    Tuple* trimmed = realloc(result, *out_n * sizeof(Tuple));
    if (trimmed != NULL) {
        result = trimmed;
    }
    
    return result;
}

int main(void) {
    Tuple arr[] = {{1, 2}, {3, 4}, {1, 2}, {5, 6}, {3, 4}, {7, 8}};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t out_n = 0;
    
    Tuple* singly = extract_singly(arr, n, &out_n);
    
    for (size_t i = 0; i < out_n; i++) {
        printf("(%d, %d)\n", singly[i].first, singly[i].second);
    }
    
    free(singly);
    
    return 0;
}