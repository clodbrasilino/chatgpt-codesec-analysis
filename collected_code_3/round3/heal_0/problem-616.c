#include <stdio.h>

typedef struct {
    int x;
    int y;
} Tuple;

Tuple modulo_tuples(Tuple t1, Tuple t2) {
    Tuple result;
    result.x = t1.x % t2.x;
    result.y = t1.y % t2.y;
    return result;
}

int main() {
    Tuple t1 = {10, 20};
    Tuple t2 = {3, 5};
    Tuple result = modulo_tuples(t1, t2);
    printf("Result: (%d, %d)\n", result.x, result.y);
    return 0;
}