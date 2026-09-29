#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_K 100

typedef struct Tuple {
    int value;
} Tuple;

bool has_all_k_elements(Tuple *tuples, int tuple_count, int k) {
    if (tuples == NULL || tuple_count <= 0 || k <= 0 || k > MAX_K) {
        return false;
    }

    bool *seen = (bool *)calloc(k, sizeof(bool));
    if (seen == NULL) {
        return false;
    }

    int found_count = 0;

    for (int i = 0; i < tuple_count; i++) {
        int idx = tuples[i].value;
        if (idx >= 0 && idx < k && !seen[idx]) {
            seen[idx] = true;
            found_count++;
        }
        if (found_count == k) {
            free(seen);
            return true;
        }
    }

    free(seen);
    return false;
}

int main() {
    Tuple test1[] = {{0}, {1}, {2}, {3}};
    int k1 = 4;
    
    printf("Test 1 (all present): %s\n", 
           has_all_k_elements(test1, 4, k1) ? "true" : "false");

    Tuple test2[] = {{0}, {1}, {2}};
    int k2 = 4;
    
    printf("Test 2 (missing element): %s\n", 
           has_all_k_elements(test2, 3, k2) ? "true" : "false");

    Tuple test3[] = {{-1}, {5}, {2}};
    int k3 = 3;
    
    printf("Test 3 (invalid values): %s\n", 
           has_all_k_elements(test3, 3, k3) ? "true" : "false");

    bool result_null = has_all_k_elements(NULL, 5, 3);
    printf("Test 4 (NULL pointer): %s\n", result_null ? "true" : "false");

    printf("Test 5 (empty list): %s\n", 
           has_all_k_elements(test1, 0, 3) ? "true" : "false");

    printf("Test 6 (k too large): %s\n", 
           has_all_k_elements(test1, 4, MAX_K + 1) ? "true" : "false");

    return 0;
}