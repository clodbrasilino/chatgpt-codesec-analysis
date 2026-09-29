#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    struct {
        int c;
        int d;
    } nested;
} Tuple;

typedef struct {
    int a;
    int b;
} SimplifiedTuple;

SimplifiedTuple removeNested(Tuple t) {
    SimplifiedTuple st;
    st.a = t.a;
    st.b = t.b;
    return st;
}

int main() {
    Tuple t;
    t.a = 1;
    t.b = 2;
    t.nested.c = 3;
    t.nested.d = 4;

    SimplifiedTuple st = removeNested(t);

    printf("Simplified Tuple: a = %d, b = %d\n", st.a, st.b);

    return 0;
}