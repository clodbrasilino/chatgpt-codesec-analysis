#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7.256, got 7
  *  test case 2 failed: expected 8.123, got 8
  *  test case 0 failed: expected 4.56, got 4
  */

double tuple_to_float(int *tuple, int size) {
    if (size != 2) {
        return 0.0;
    }
    double result = (double)tuple[0] + (double)tuple[1] / 100.0;
    return result;
}

int main() {
    int tuple[] = {3, 50};
    int size = 2;
    double float_value = tuple_to_float(tuple, size);
    printf("%.3f\n", float_value);
    return 0;
}