#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

Tuple* extract_elementwise_tuples(Tuple* t1, Tuple* t2, int n) {
    if (n <= 0) return NULL;
    Tuple* result = (Tuple*)malloc(n * sizeof(Tuple));
    for (int i = 0; i < n; ++i) {
        result[i].x = t1[i].x + t2[i].x;
        result[i].y = t1[i].y + t2[i].y;
    }
    return result;
}

void free_tuples(Tuple* tuples) {
    free(tuples);
}

int main() {
    int n = 3;
    Tuple t1[3] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple t2[3] = {{7, 8}, {9, 10}, {11, 12}};
    
    Tuple* result = extract_elementwise_tuples(t1, t2, n);
    if (result != NULL) {
        for (int i = 0; i < n; ++i) {
            printf("(%d, %d)\n", result[i].x, result[i].y);
        }
        free_tuples(result);
    }
    
    return 0;
}