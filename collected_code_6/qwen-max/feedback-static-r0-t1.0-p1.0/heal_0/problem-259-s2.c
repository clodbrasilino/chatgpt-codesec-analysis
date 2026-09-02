#include <stdio.h>
#include <stdint.h>

typedef struct {
    int32_t first;
    int32_t second;
} tuple;

tuple maximize_tuples(tuple t1, tuple t2) {
    tuple result;
    result.first = (t1.first > t2.first) ? t1.first : t2.first;
    result.second = (t1.second > t2.second) ? t1.second : t2.second;
    return result;
}

int main(void) {
    tuple t1 = {5, 10};
    tuple t2 = {15, 8};
    tuple max_tuple = maximize_tuples(t1, t2);
    printf("Max Tuple: (%d, %d)\n", max_tuple.first, max_tuple.second);
    return 0;
}