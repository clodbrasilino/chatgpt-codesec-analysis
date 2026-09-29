#include <stdio.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple maximize_tuples(Tuple t1, Tuple t2) {
    Tuple result;
    result.a = (t1.a > t2.a) ? t1.a : t2.a;
    result.b = (t1.b > t2.b) ? t1.b : t2.b;
    return result;
}

int main(void) {
    Tuple tuple1 = {5, 10};
    Tuple tuple2 = {8, 3};
    Tuple max_tuple;

    max_tuple = maximize_tuples(tuple1, tuple2);

    printf("Tuple 1: (%d, %d)\n", tuple1.a, tuple1.b);
    printf("Tuple 2: (%d, %d)\n", tuple2.a, tuple2.b);
    printf("Maximized Tuple: (%d, %d)\n", max_tuple.a, max_tuple.b);

    return 0;
}