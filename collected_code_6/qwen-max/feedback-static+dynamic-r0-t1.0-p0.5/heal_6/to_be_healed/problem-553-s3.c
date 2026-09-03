#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7.256, got 7
  *  test case 2 failed: expected 8.123, got 8
  *  test case 0 failed: expected 4.56, got 4
  */

double tuple_to_float(const int *tuple, size_t len) {
    if (len != 2) {
        return -1.0;
    }
    double result = (double)tuple[0] + (double)tuple[1] / 1000.0;
    return result;
}

int main() {
    int test_cases[][2] = {{7256, 256}, {8123, 123}, {456, 560}};
    size_t num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    for (size_t i = 0; i < num_test_cases; ++i) {
        double float_value = (double)test_cases[i][0] + (double)test_cases[i][1] / 1000.0;
        printf("%.3f\n", float_value);
    }
    return 0;
}