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
    double result = (double)tuple[0] + (double)tuple[1] / 1000.0;
    return result;
}

int main() {
    int tuple1[] = {7, 256};
    int size1 = 2;
    double float_value1 = (double)tuple1[0] + (double)(tuple1[1] % 1000) / 1000.0;
    printf("%.3f\n", float_value1);

    int tuple2[] = {8, 123};
    int size2 = 2;
    double float_value2 = (double)tuple2[0] + (double)(tuple2[1] % 1000) / 1000.0;
    printf("%.3f\n", float_value2);

    int tuple0[] = {4, 560};
    int size0 = 2;
    double float_value0 = (double)tuple0[0] + (double)(tuple0[1] % 1000) / 1000.0;
    printf("%.3f\n", float_value0);

    return 0;
}