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
    tuple.first = 1;
    tuple.second = 2;

    printf("First element of the tuple: %d\n", getFirst(tuple));

    return 0;
}