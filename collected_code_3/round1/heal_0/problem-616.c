#include <stdio.h>

typedef struct {
    int x;
    int y;
} Tuple;

Tuple moduloTuple(Tuple a, Tuple b) {
    Tuple result;
    result.x = a.x % b.x;
    result.y = a.y % b.y;
    return result;
}

int main() {
    Tuple t1 = {10, 20};
    Tuple t2 = {3, 5};
    Tuple result = moduloTuple(t1, t2);
    printf("Result: (%d, %d)\n", result.x, result.y);
    return 0;
}