#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 8.123, got <no output>
  *  test case 1 failed: expected 7.256, got <no output>
  *  test case 0 failed: expected 4.56, got <no output>
  */

double tuple_to_float(const char *tuple) {
    double num1, num2;
    if (sscanf(tuple, "(%lf,%lf)", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input format\n");
        exit(EXIT_FAILURE);
    }
    return num1 + num2;
}

int main() {
    const char *test_cases[] = {"(4.56,0.0)", "(7.256,0.867)", "(8.123,0.0)"};
    for (int i = 0; i < 3; i++) {
        double result = tuple_to_float(test_cases[i]);
        printf("Result: %f\n", result);
    }
    return 0;
}