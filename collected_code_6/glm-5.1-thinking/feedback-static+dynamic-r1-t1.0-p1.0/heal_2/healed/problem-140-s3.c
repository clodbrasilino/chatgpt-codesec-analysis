#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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

    if (n > SIZE_MAX / sizeof(Tuple)) {
        return NULL;
    }
    
    size_t total_size = n * sizeof(Tuple);
    
    Tuple* sorted = malloc(total_size);
    if (sorted == NULL) {
        return NULL;
    }
    
    for (size_t j = 0; j < n; j++) {
        sorted[j] = arr[j];
    }
    
    qsort(sorted, n, sizeof(Tuple), tuple_compare);
    
    Tuple* result = malloc(total_size);
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
    
    size_t trimmed_size = *out_n * sizeof(Tuple);
    Tuple* trimmed = realloc(result, trimmed_size);
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