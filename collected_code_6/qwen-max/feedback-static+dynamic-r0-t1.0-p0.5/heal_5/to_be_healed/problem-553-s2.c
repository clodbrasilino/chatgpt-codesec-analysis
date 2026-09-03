#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7.256, got -1
  *  test case 2 failed: expected 8.123, got -1
  *  test case 0 failed: expected 4.56, got -1
  */

double tuple_to_float(const char *tuple) {
    double result;
    if (sscanf(tuple, "(%lf)", &result) != 1) {
        return -1.0;
    }
    return result;
}

int main() {
    const char *inputs[] = {"(4.56)", "(7.256)", "(8.123)"};
    for (size_t i = 0; i < 3; ++i) {
        double output = tuple_to_float(inputs[i]);
        if (output != -1.0) {
            printf("Converted float: %f\n", output);
        } else {
            fprintf(stderr, "Error: Invalid input format for %s\n", inputs[i]);
        }
    }
    return 0;
}