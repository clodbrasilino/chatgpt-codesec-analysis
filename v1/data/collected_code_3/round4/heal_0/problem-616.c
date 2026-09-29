#include <stdio.h>

typedef struct {
    int x;
    int y;
} Tuple;

Tuple modulo_tuples(Tuple a, Tuple b) {
    Tuple result;
    result.x = a.x % b.x;
    result.y = a.y % b.y;
    return result;
}

int main() {
    Tuple a = {10, 20};
    Tuple b = {3, 5};
    Tuple result = modulo_tuples(a, b);
    printf("Result: (%d, %d)\n", result.x, result.y);
    return 0;
}