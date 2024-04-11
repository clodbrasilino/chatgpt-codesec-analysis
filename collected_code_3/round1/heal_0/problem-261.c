#include <stdio.h>

typedef struct {
    int a;
    int b;
} Tuple;

double divide(Tuple t) {
    if(t.b == 0) {
        printf("Error: Division by zero\n");
        return 0;
    }
    return (double)t.a / t.b;
}

int main() {
    Tuple t1 = {10, 2};
    Tuple t2 = {20, 5};
    Tuple t3 = {30, 0};

    printf("Result of division of tuple t1: %.2f\n", divide(t1));
    printf("Result of division of tuple t2: %.2f\n", divide(t2));
    printf("Result of division of tuple t3: %.2f\n", divide(t3));

    return 0;
}