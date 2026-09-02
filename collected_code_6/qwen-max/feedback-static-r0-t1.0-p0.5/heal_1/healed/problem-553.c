#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double tuple_to_float(const int *tuple, size_t length) {
    if (length == 0) return 0.0;
    double result = 0.0;
    for (size_t i = 0; i < length; ++i) {
        result += tuple[i] * pow(10, length - i - 1);
    }
    return result;
}

int main() {
    int tuple[] = {1, 2, 3, 4};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    double float_value = tuple_to_float(tuple, length);
    printf("%.1f\n", float_value);
    return 0;
}