#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct {
    int x;
    int y;
    int z;
} Tuple;

int getColonOfTuple(Tuple t) {
    return t.y;
}

int main() {
    Tuple t = {1, 2, 3};
    printf("Colon of the tuple: %d\n", getColonOfTuple(t));
    return 0;
}