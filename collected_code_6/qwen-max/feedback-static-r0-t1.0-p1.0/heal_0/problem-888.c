#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

Tuple subtract_tuples(Tuple a, Tuple b) {
    Tuple result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

int main() {
    Tuple t1 = {5, 10};
    Tuple t2 = {3, 7};
    Tuple result = subtract_tuples(t1, t2);
    printf("Result: (%d, %d)\n", result.x, result.y);
    return 0;
}