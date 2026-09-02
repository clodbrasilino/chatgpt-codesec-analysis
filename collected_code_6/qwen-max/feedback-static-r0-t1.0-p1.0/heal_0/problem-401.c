#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

typedef struct {
    Tuple t1;
    Tuple t2;
} NestedTuple;

NestedTuple add_nested_tuples(NestedTuple nt1, NestedTuple nt2) {
    NestedTuple result;
    result.t1.x = nt1.t1.x + nt2.t1.x;
    result.t1.y = nt1.t1.y + nt2.t1.y;
    result.t2.x = nt1.t2.x + nt2.t2.x;
    result.t2.y = nt1.t2.y + nt2.t2.y;
    return result;
}

int main() {
    NestedTuple nt1 = {{1, 2}, {3, 4}};
    NestedTuple nt2 = {{5, 6}, {7, 8}};
    
    NestedTuple result = add_nested_tuples(nt1, nt2);
    
    printf("Result: ((%d, %d), (%d, %d))\n", result.t1.x, result.t1.y, result.t2.x, result.t2.y);
    
    return 0;
}