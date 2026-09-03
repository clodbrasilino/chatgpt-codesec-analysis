#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7.256, got <no output>
  *  test case 2 failed: expected 8.123, got <no output>
  *  test case 0 failed: expected 4.56, got <no output>
  */

double tuple_to_float(const char *tuple) {
    double result;
    if (sscanf(tuple, "(%lf)", &result) != 1) {
        printf("Invalid input format\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

int main() {
    const char *test_cases[] = {"(4.56)", "(7.256)", "(8.123)"};
    for (int i = 0; i < 3; i++) {
        double output = tuple_to_float(test_cases[i]);
        printf("%.3f\n", output);
    }
    return 0;
}