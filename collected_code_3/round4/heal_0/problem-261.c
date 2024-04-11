#include <stdio.h>

typedef struct {
    double x;
    double y;
} Tuple;

Tuple divide(Tuple a, Tuple b) {
    Tuple result;
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    return result;
}

int main() {
    Tuple a = {10.0, 20.0};
    Tuple b = {2.0, 5.0};
    Tuple result = divide(a, b);
    printf("Result: (%f, %f)\n", result.x, result.y);
    return 0;
}