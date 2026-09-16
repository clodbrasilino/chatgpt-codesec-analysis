#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple2;

typedef struct {
    int a1;
    int b1;
    int a2;
    int b2;
} Tuple4;

Tuple4 zip_tuples(Tuple2 t1, Tuple2 t2) {
    Tuple4 result;
    result.a1 = t1.a;
    result.b1 = t1.b;
    result.a2 = t2.a;
    result.b2 = t2.b;
    return result;
}

int main() {
    Tuple2 t1 = {1, 2};
    Tuple2 t2 = {3, 4};
    Tuple4 zipped = zip_tuples(t1, t2);
    printf("%d %d %d %d\n", zipped.a1, zipped.b1, zipped.a2, zipped.b2);
    return 0;
}