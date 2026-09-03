#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 8.123, got <no output>
  *  test case 0 failed: expected 4.56, got <no output>
  *  test case 1 failed: expected 7.256, got <no output>
  */

double tuple_to_float(const char *tuple) {
    double result;
    if (sscanf(tuple, "(%lf)", &result) != 1) {
        fprintf(stderr, "Error: Invalid input format\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

int main() {
    const char *input = "(3.14)";
    double output = tuple_to_float(input);
    printf("Converted float: %f\n", output);
    return 0;
}