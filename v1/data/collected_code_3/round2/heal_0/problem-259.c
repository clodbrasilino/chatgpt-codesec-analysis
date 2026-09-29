#include <stdio.h>

typedef struct {
    int x;
    int y;
} Tuple;

Tuple maximize(Tuple a, Tuple b) {
    Tuple max;
    max.x = (a.x > b.x) ? a.x : b.x;
    max.y = (a.y > b.y) ? a.y : b.y;
    return max;
}

int main() {
    Tuple a = {3, 5};
    Tuple b = {4, 2};
    Tuple max = maximize(a, b);
    printf("Maximized tuple: (%d, %d)\n", max.x, max.y);
    return 0;
}