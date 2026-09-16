#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple t1;
    Tuple t2;
} NestedTuple;

int subtract_nested_tuples(NestedTuple *nt, int *out_a, int *out_b) {
    if (nt == NULL || out_a == NULL || out_b == NULL) {
        return -1;
    }

    *out_a = nt->t1.a - nt->t2.a;
    *out_b = nt->t1.b - nt->t2.b;

    return 0;
}

int main() {
    NestedTuple nt;
    int a, b;

    nt.t1.a = 20;
    nt.t1.b = 30;
    nt.t2.a = 5;
    nt.t2.b = 10;

    if (subtract_nested_tuples(&nt, &a, &b) != 0) {
        return EXIT_FAILURE;
    }

    printf("%d %d\n", a, b);

    return EXIT_SUCCESS;
}