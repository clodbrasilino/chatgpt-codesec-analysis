#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple subtract_tuples(Tuple t1, Tuple t2) {
    Tuple result;
    result.first = t1.first - t2.first;
    result.second = t1.second - t2.second;
    return result;
}

int main() {
    Tuple t1 = {5, 10};
    Tuple t2 = {3, 8};
    Tuple result = subtract_tuples(t1, t2);
    printf("Result: (%d, %d)\n", result.first, result.second);
    return 0;
}