#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple 
{
    int a;
    int b;
} Tuple;

int getSecondElement(Tuple tuple)
{
    return tuple.b;
}

int main() 
{
    Tuple tuple;
    tuple.a = 1;
    tuple.b = 2;
    printf("Second element of the tuple is: %d\n", getSecondElement(tuple));
    return 0;
}