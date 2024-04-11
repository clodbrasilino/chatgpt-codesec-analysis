#include <stdio.h>

typedef struct {
    int x;
    int y;
} Tuple;

void clearTuple(Tuple *t) {
    t->x = 0;
    t->y = 0;
}

int main() {
    Tuple t1 = {5, 10};
    Tuple t2 = {20, 30};

    clearTuple(&t1);
    clearTuple(&t2);

    printf("t1: (%d, %d)\n", t1.x, t1.y);
    printf("t2: (%d, %d)\n", t2.x, t2.y);

    return 0;
}