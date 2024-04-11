#include <stdio.h>

typedef struct {
    int a;
    int b;
} Tuple;

void repeatTuple(Tuple t, int n) {
    for(int i = 0; i < n; i++) {
        printf("(%d, %d)\n", t.a, t.b);
    }
}

int main() {
    Tuple t;
    t.a = 5;
    t.b = 10;
    repeatTuple(t, 3);
    return 0;
}