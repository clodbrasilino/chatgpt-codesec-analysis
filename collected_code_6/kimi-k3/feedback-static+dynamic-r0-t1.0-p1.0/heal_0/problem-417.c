#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int find_common_first(const Tuple *tuples, size_t count, int *result) {
    if (tuples == NULL || result == NULL || count == 0) {
        return 0;
    }
    
    *result = tuples[0].first;
    
    for (size_t i = 1; i < count; i++) {
        if (tuples[i].first != *result) {
            return 0;
        }
    }
    
    return 1;
}

int main(void) {
    Tuple tuples[] = {{5, 10}, {5, 20}, {5, 30}, {5, 40}};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    int common_first;
    
    if (find_common_first(tuples, count, &common_first)) {
        printf("Common first element: %d\n", common_first);
    } else {
        printf("No common first element found\n");
    }
    
    return 0;
}