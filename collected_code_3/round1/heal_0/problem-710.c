#include <stdio.h>

typedef struct {
    int initial;
    int last;
} Tuple;

void accessData(Tuple *t) {
    printf("Initial data: %d\n", t->initial);
    printf("Last data: %d\n", t->last);
}

int main() {
    Tuple t;
    t.initial = 10;
    t.last = 20;

    accessData(&t);

    return 0;
}