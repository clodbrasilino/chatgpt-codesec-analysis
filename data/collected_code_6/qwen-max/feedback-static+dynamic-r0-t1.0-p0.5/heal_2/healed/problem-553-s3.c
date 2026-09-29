#include <stdio.h>
#include <stdlib.h>

double tuple_to_float(const int *tuple, size_t len) {
    if (len != 2) {
        return -1.0;
    }
    double result = (double)tuple[0] + (double)tuple[1] / 100.0;
    return result;
}

int main() {
    int test_cases[][2] = {{7, 25}, {8, 12}, {4, 56}};
    size_t num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    for (size_t i = 0; i < num_test_cases; ++i) {
        double float_value = tuple_to_float(test_cases[i], 2);
        if (float_value >= 0.0) {
            printf("%.3f\n", float_value);
        } else {
            printf("Invalid tuple length\n");
        }
    }
    return 0;
}