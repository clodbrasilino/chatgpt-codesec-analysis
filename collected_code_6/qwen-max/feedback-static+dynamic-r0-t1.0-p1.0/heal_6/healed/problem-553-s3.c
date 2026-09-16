#include <stdio.h>
#include <stdlib.h>

double tuple_to_float(int *tuple, int size) {
    if (size != 2) {
        return 0.0;
    }
    double result = (double)tuple[0] + (double)(tuple[1] % 1000) / 1000.0;
    return result;
}

int main() {
    int test_cases[][2] = {{4, 560}, {7, 256}, {8, 123}};
    for (int i = 0; i < 3; i++) {
        double float_value = tuple_to_float(test_cases[i], 2);
        printf("%.3f\n", float_value);
    }
    return 0;
}