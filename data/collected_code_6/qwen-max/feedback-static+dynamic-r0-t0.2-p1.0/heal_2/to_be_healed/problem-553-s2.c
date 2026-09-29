#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 8.123, got 8
  *  test case 0 failed: expected 4.56, got 4
  *  test case 1 failed: expected 7.256, got 7
  */

double tuple_to_float(const int *tuple, size_t len) {
    if (len != 2) {
        return 0.0;
    }
    double result = (double)tuple[0] + (double)tuple[1] / 100.0;
    return result;
}

int main() {
    int tuple[] = {123, 45};
    size_t len = sizeof(tuple) / sizeof(tuple[0]);
    double float_value = tuple_to_float(tuple, len);
    printf("%.3f\n", float_value);
    return 0;
}