#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple2;

typedef struct {
    int a;
    int b;
    int c;
    int d;
} Tuple4;

Tuple4 zip_tuples(Tuple2 t1, Tuple2 t2) {
    Tuple4 result;
    result.a = t1.a;
    result.b = t1.b;
    result.c = t2.a;
    result.d = t2.b;
    return result;
}

int main() {
    Tuple2 t1 = {1, 2};
    Tuple2 t2 = {3, 4};
    
    Tuple4 zipped = zip_tuples(t1, t2);
    
    printf("(%d, %d, %d, %d)\n", zipped.a, zipped.b, zipped.c, zipped.d);
    
    return 0;
}