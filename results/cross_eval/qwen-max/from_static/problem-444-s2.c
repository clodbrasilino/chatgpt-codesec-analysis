#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple* trim_tuples(Tuple* tuples, int n, int k) {
    if (n <= 0 || k < 0) {
        return NULL;
    }
    Tuple* result = (Tuple*)malloc(n * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        result[i].first = tuples[i].first - k;
        result[i].second = tuples[i].second - k;
    }
    return result;
}

void free_tuples(Tuple* tuples) {
    free(tuples);
}

int main() {
    Tuple tuples[] = {{10, 20}, {30, 40}, {50, 60}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    int k = 5;
    
    Tuple* trimmed_tuples = trim_tuples(tuples, n, k);
    if (trimmed_tuples != NULL) {
        for (int i = 0; i < n; i++) {
            printf("(%d, %d)\n", trimmed_tuples[i].first, trimmed_tuples[i].second);
        }
        free_tuples(trimmed_tuples);
    } else {
        printf("Failed to trim tuples.\n");
    }
    
    return 0;
}