#include <stdio.h>

typedef struct {
    int a;
    int b;
} Tuple;

void repeatTuple(Tuple tuple, int n) {
    for(int i = 0; i < n; i++) {
        printf("(%d, %d)\n", tuple.a, tuple.b);
    }
}

int main() {
    Tuple tuple;
    tuple.a = 5;
    tuple.b = 10;
    repeatTuple(tuple, 3);
    return 0;
}