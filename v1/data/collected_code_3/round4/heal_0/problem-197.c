#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Tuple;

Tuple exponentiate(Tuple a, Tuple b) {
    Tuple result;
    result.x = pow(a.x, b.x);
    result.y = pow(a.y, b.y);
    return result;
}

int main() {
    Tuple a = {2.0, 3.0};
    Tuple b = {3.0, 2.0};
    Tuple result = exponentiate(a, b);
    printf("Result: (%.2f, %.2f)\n", result.x, result.y);
    return 0;
}