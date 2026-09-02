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

    bool *seen = (bool *)calloc((size_t)k, sizeof(bool));
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

bool has_all_k_elements_null_safe(Tuple *tuples, int tuple_count, int k) {
    if (tuples == NULL) {
        return false;
    }
    return has_all_k_elements(tuples, tuple_count, k);
}

int main(void) {
    Tuple test1[] = {{0}, {1}, {2}, {3}};
    int k1 = 4;
    
    bool result1 = has_all_k_elements(test1, 4, k1);
    if (result1) {
        printf("Test 1 (all present): true\n");
    } else {
        printf("Test 1 (all present): false\n");
    }

    Tuple test2[] = {{0}, {1}, {2}};
    int k2 = 4;
    
    bool result2 = has_all_k_elements(test2, 3, k2);
    if (result2) {
        printf("Test 2 (missing element): true\n");
    } else {
        printf("Test 2 (missing element): false\n");
    }

    Tuple test3[] = {{-1}, {5}, {2}};
    int k3 = 3;
    
    bool result3 = has_all_k_elements(test3, 3, k3);
    if (result3) {
        printf("Test 3 (invalid values): true\n");
    } else {
        printf("Test 3 (invalid values): false\n");
    }

    Tuple *null_tuples = NULL;
    bool result4 = has_all_k_elements_null_safe(null_tuples, 5, 3);
    if (result4) {
        printf("Test 4 (NULL pointer): true\n");
    } else {
        printf("Test 4 (NULL pointer): false\n");
    }

    bool result5 = has_all_k_elements(test1, 0, 3);
    if (result5) {
        printf("Test 5 (empty list): true\n");
    } else {
        printf("Test 5 (empty list): false\n");
    }

    bool result6 = has_all_k_elements(test1, 4, MAX_K + 1);
    if (result6) {
        printf("Test 6 (k too large): true\n");
    } else {
        printf("Test 6 (k too large): false\n");
    }

    return 0;
}