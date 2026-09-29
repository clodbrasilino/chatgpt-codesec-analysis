#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple maximize_tuples(Tuple t1, Tuple t2) {
    Tuple result;
    result.first = (t1.first > t2.first) ? t1.first : t2.first;
    result.second = (t1.second > t2.second) ? t1.second : t2.second;
    return result;
}

int main(void) {
    Tuple t1 = {5, 10};
    Tuple t2 = {7, 8};
    Tuple max_tuple;

    max_tuple = maximize_tuples(t1, t2);

    printf("(%d, %d)\n", max_tuple.first, max_tuple.second);

    return 0;
}