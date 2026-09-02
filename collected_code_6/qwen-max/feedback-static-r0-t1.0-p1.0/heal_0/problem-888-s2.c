#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple subtract_tuples(Tuple a, Tuple b) {
    Tuple result;
    result.first = a.first - b.first;
    result.second = a.second - b.second;
    return result;
}

int main() {
    Tuple t1 = {5, 3};
    Tuple t2 = {2, 1};

    Tuple result = subtract_tuples(t1, t2);

    printf("Result: (%d, %d)\n", result.first, result.second);
    return 0;
}