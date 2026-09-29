#include <stdio.h>

typedef struct {
    int a;
    float b;
} Tuple;

typedef struct {
    Tuple t1;
    Tuple t2;
} NestedTuple;

NestedTuple concatenate_tuples(Tuple t1, Tuple t2) {
    NestedTuple nt;
    nt.t1 = t1;
    nt.t2 = t2;
    return nt;
}

int main() {
    Tuple t1 = {1, 2.0};
    Tuple t2 = {3, 4.0};
    NestedTuple nt = concatenate_tuples(t1, t2);
    printf("Nested Tuple: ((%d, %.1f), (%d, %.1f))\n", nt.t1.a, nt.t1.b, nt.t2.a, nt.t2.b);
    return 0;
}