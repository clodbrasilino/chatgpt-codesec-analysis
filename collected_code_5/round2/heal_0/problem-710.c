#include <stdio.h>

typedef struct {
    int a;
    int b;
    int c;
} Tuple;

void printFirstAndLast(Tuple tuple) {
    printf("First: %d\n", tuple.a);
    printf("Last: %d\n", tuple.c);
}

int main(void) {
    Tuple t1 = {10, 20, 30};
    printFirstAndLast(t1);
    return 0;
}