#include <stdio.h>
#include <stdlib.h>

double tuple_to_float(const char *tuple) {
    double num1, num2;
    if (sscanf(tuple, "(%lf,%lf)", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input format\n");
        exit(EXIT_FAILURE);
    }
    return num1 + num2;
}

int main() {
    const char *tuple = "(3.5,6.5)";
    double result = tuple_to_float(tuple);
    printf("Result: %f\n", result);
    return 0;
}