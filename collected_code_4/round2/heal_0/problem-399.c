#include <stdio.h>

typedef struct tuple {
    int a;
    int b;
} Tuple;

int perform_xor(Tuple t) {
    return t.a ^ t.b;
}

int main() {
    Tuple t1;
    t1.a = 12;
    t1.b = 25;
    
    printf("The XOR of %d and %d is %d\n", t1.a, t1.b, perform_xor(t1));

    return 0;
}