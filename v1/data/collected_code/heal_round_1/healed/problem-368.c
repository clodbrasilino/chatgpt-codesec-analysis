#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int c;
} Tuple;

Tuple* repeatTuple(Tuple* tup, int n) {
    if (tup == NULL || n <= 0) {
        return NULL;
    }

    Tuple* result = (Tuple*)malloc(n * sizeof(Tuple));

    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        result[i].a = tup->a;
        result[i].b = tup->b;
        result[i].c = tup->c;
    }
    
    return result;
}

int main() {
    Tuple test = {1, 2, 3};
    Tuple* repeat = repeatTuple(&test, 5);
    if (repeat != NULL) {
        for (int i = 0; i < 5; i++) {
            printf("Tuple %d: %d, %d, %d\n", i+1, repeat[i].a, repeat[i].b, repeat[i].c);
        }
        free(repeat);
    }
    return 0;
}