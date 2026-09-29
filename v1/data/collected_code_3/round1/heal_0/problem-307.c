#include <stdio.h>

typedef struct {
    int first;
    int second;
} Tuple;

int getFirst(Tuple tuple) {
    return tuple.first;
}

int main() {
    Tuple tuple;
    tuple.first = 5;
    tuple.second = 10;

    printf("First element of the tuple is %d\n", getFirst(tuple));

    return 0;
}