#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple max_tuples(Tuple t1, Tuple t2) {
    Tuple result;
    result.a = t1.a > t2.a ? t1.a : t2.a;
    result.b = t1.b > t2.b ? t1.b : t2.b;
    return result;
}

int main(void) {
    Tuple t1 = {3, 7};
    Tuple t2 = {5, 2};
    Tuple result = max_tuples(t1, t2);
    printf("%d %d\n", result.a, result.b);
    return 0;
}