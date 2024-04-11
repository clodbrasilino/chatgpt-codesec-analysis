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
    Tuple a, b, result;
    a.x = 10;
    a.y = 20;
    b.x = 3;
    b.y = 5;

    result = moduloTuple(a, b);

    printf("Result: (%d, %d)\n", result.x, result.y);

    return 0;
}