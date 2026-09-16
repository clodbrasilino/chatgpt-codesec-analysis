#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
} Tuple;

bool find_common_first(const Tuple *tuples, size_t size, int *result) {
    if (tuples == NULL || result == NULL || size == 0) {
        return false;
    }
    
    int candidate = tuples[0].first;
    
    for (size_t i = 1; i < size; i++) {
        if (tuples[i].first != candidate) {
            return false;
        }
    }
    
    *result = candidate;
    return true;
}

int main(void) {
    Tuple tuples[] = {{5}, {5}, {5}, {5}};
    size_t size = sizeof(tuples) / sizeof(tuples[0]);
    int common_value;
    
    if (find_common_first(tuples, size, &common_value)) {
        printf("Common first element: %d\n", common_value);
    } else {
        printf("No common first element found.\n");
    }
    
    return 0;
}