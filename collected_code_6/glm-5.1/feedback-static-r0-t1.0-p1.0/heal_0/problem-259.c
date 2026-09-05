#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple maximize_tuples(Tuple t1, Tuple t2) {
    Tuple res;
    res.a = t1.a > t2.a ? t1.a : t2.a;
    res.b = t1.b > t2.b ? t1.b : t2.b;
    return res;
}

int main() {
    Tuple t1 = {5, 10};
    Tuple t2 = {15, 3};
    Tuple res = maximize_tuples(t1, t2);
    printf("%d %d\n", res.a, res.b);
    return 0;
}