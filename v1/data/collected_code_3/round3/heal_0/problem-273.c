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
    Tuple tuple1 = {10, 20};
    Tuple tuple2 = {5, 15};
    Tuple result = subtractTuples(tuple1, tuple2);
    printf("Result: (%d, %d)\n", result.a, result.b);
    return 0;
}