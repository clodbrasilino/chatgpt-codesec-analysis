#include <stdio.h>
#include <stdlib.h>

int divide(int a, int b, int *result) {
    if (b == 0) {
        return -1;
    }
    *result = a / b;
    return 0;
}

int main() {
    int num1 = 10, num2 = 0, result;
    int status = divide(num1, num2, &result);
    if (status == 0) {
        printf("Quotient: %d\n", result);
    } else {
        fprintf(stderr, "Error: Division by zero\n");
    }
    return 0;
}