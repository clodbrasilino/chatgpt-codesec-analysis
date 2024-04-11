#include <stdio.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple subtractTuples(Tuple t1, Tuple t2) {
    Tuple result;
    result.a = t1.a - t2.a;
    result.b = t1.b - t2.b;
    return result;
}

int main() {
    Tuple t1 = {10, 20};
    Tuple t2 = {5, 15};
    Tuple result = subtractTuples(t1, t2);
    printf("Result: (%d, %d)\n", result.a, result.b);
    return 0;
}