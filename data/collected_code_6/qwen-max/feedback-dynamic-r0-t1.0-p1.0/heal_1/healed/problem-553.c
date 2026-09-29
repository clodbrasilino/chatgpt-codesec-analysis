#include <stdio.h>
#include <stdlib.h>

double tuple_to_float(const char *tuple) {
    char *end;
    double num1, num2;
    if (sscanf(tuple, "(%lf,%lf)", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input format\n");
        exit(EXIT_FAILURE);
    }
    return num1 + num2;
}

int main() {
    const char *test_cases[] = {"(4.56,0.0)", "(3.5,6.5)", "(1.885,6.238)"};
    double expected_results[] = {4.56, 10.0, 8.123};

    for (int i = 0; i < 3; ++i) {
        double result = tuple_to_float(test_cases[i]);
        printf("Test case %d: Expected %f, Got %f\n", i, expected_results[i], result);
    }

    return 0;
}