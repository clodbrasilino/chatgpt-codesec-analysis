#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* repeat_tuple(Tuple tuple, int n) {
    if(n <= 0) return NULL;
    Tuple* result = (Tuple*)malloc(sizeof(Tuple) * n);
    if(result == NULL) return NULL;
    for(int i = 0; i < n; i++) {
        result[i] = tuple;
    }
    return result;
}

void free_memory(Tuple* tuples, int n) {
    if(tuples == NULL || n <= 0) return;
    free(tuples);
}

int main() {
    Tuple tuple = {5, 10};
    int n = 3;

    Tuple* tuples = repeat_tuple(tuple, n);
    if(tuples == NULL) {
        printf("Unable to allocate memory!\n");
        return 1;
    }

    for(int i = 0; i < n; i++) {
        printf("tuple[%d] = (%d,%d)\n", i, tuples[i].a, tuples[i].b);
    }

    free_memory(tuples, n);

    return 0;
}
