#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Tuple;

Tuple pow_tuple(Tuple a, Tuple b) {
    Tuple result;
    if (a.x < 0 || b.x < 0 || a.y < 0 || b.y < 0) {
        printf("Error: negative bases not allowed\n");
        result.x = 0;
        result.y = 0;
        return result;
    }
    result.x = pow(a.x, b.x);
    result.y = pow(a.y, b.y);
    return result;
}

int main() {
    Tuple a = {2.0, 3.0};
    Tuple b = {2.0, 2.0};
    Tuple result = pow_tuple(a, b);
    printf("X: %.2f, Y:%.2f\n", result.x, result.y);
    return 0;
}