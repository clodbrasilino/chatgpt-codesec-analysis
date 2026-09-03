#include <stdio.h>
#include <stdlib.h>

double tuple_to_float(const char *tuple) {
    char *end;
    double num1 = 0, num2 = 0;
    if (sscanf(tuple, "(%lf,%lf)", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input format\n");
        exit(EXIT_FAILURE);
    }
    return num1 + num2;
}

int main() {
    const char *test_cases[] = {"(4.56,0.0)", "(7.256,0.0)", "(8.123,0.0)"};
    double expected_results[] = {4.56, 7.256, 8.123};
    int passed = 1;

    for (int i = 0; i < 3; ++i) {
        double result = tuple_to_float(test_cases[i]);
        if (result != expected_results[i]) {
            printf("Test case %d: Expected %.3f, Got %.3f\n", i, expected_results[i], result);
            passed = 0;
        } else {
            printf("Test case %d: Passed\n", i);
        }
    }

    if (passed) {
        printf("All test cases passed.\n");
    }

    return 0;
}