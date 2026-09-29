#include <stdio.h>

typedef struct {
    int a;
    double b;
    char c;
} Tuple;

int getTupleSize(Tuple tuple) {
    return sizeof(tuple);
}

int main() {
    Tuple tuple = {1, 2.0, 'a'};
    printf("Size of tuple: %d bytes\n", getTupleSize(tuple));
    return 0;
}