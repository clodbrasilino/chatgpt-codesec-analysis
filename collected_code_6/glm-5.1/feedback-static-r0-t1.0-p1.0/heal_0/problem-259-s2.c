#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple maximize_tuples(Tuple t1, Tuple t2) {
    Tuple result;
    result.a = t1.a > t2.a ? t1.a : t2.a;
    result.b = t1.b > t2.b ? t1.b : t2.b;
    return result;
}

int main() {
    Tuple t1 = {5, 10};
    Tuple t2 = {15, 3};
    Tuple max_tuple = maximize_tuples(t1, t2);
    printf("%d, %d\n", max_tuple.a, max_tuple.b);
    return EXIT_SUCCESS;
}