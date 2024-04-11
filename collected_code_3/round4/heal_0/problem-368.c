#include <stdio.h>

typedef struct {
    int first;
    int second;
} Tuple;

void repeatTuple(Tuple tuple, int n) {
    for(int i = 0; i < n; i++) {
        printf("(%d, %d)\n", tuple.first, tuple.second);
    }
}

int main() {
    Tuple tuple;
    tuple.first = 1;
    tuple.second = 2;
    repeatTuple(tuple, 5);
    return 0;
}