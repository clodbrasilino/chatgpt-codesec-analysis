#include <stdio.h>

typedef struct 
{
    int a;
    int b;
} Tuple;

int xorOperation(Tuple tuple) 
{
    return tuple.a ^ tuple.b;
}

int main()
{
    Tuple tuple = {3, 6};
    printf("The xor result of %d and %d is: %d\n", tuple.a, tuple.b, xorOperation(tuple));
    return 0;
}