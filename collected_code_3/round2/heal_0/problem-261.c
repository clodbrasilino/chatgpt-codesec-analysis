#include <stdio.h>

typedef struct {
    double a;
    double b;
} Tuple;

double divideTuples(Tuple t1, Tuple t2) {
    if(t2.a == 0 || t2.b == 0) {
        printf("Error: Division by zero is not allowed.\n");
        return -1;
    }
    double resultA = t1.a / t2.a;
    double resultB = t1.b / t2.b;
    return (resultA + resultB) / 2;
}

int main() {
    Tuple t1 = {10.0, 20.0};
    Tuple t2 = {2.0, 4.0};
    double result = divideTuples(t1, t2);
    if(result != -1) {
        printf("The result is: %.2f\n", result);
    }
    return 0;
}