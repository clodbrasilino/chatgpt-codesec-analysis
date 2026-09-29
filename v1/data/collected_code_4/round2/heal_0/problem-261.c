#include <stdio.h>

typedef struct Tuple {
    int dividend;
    int divisor;
} Tuple;

double performDivision(Tuple tuple);

int main() {
    Tuple tuple;
    tuple.dividend = 10;
    tuple.divisor = 2;

    double result = performDivision(tuple);
    printf("Result is : %f \n", result);

    tuple.dividend = 10;
    tuple.divisor = 0;
    
    result = performDivision(tuple);
    printf("Result is : %f \n", result);

    return 0;
}

double performDivision(Tuple tuple) {
    double result = 0;
    if (tuple.divisor == 0) {
        printf("Error! Division by zero is not allowed.\n");
    } else {
        result = (double) tuple.dividend / tuple.divisor;
    }
    return result;
}