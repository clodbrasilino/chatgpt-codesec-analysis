#include <stdio.h>
#include <stdlib.h>

double tuple_to_float(const int *tuple, size_t len) {
    if (len != 2) {
        return 0.0;
    }
    double result = (double)tuple[0] + (double)tuple[1] / 1000.0;
    return result;
}

int main() {
    int tuple[] = {8, 123};
    size_t len = sizeof(tuple) / sizeof(tuple[0]);
    double float_value = tuple_to_float(tuple, len);
    printf("%.4f\n", float_value);

    int tuple2[] = {4, 560};
    len = sizeof(tuple2) / sizeof(tuple2[0]);
    float_value = tuple_to_float(tuple2, len);
    printf("%.4f\n", float_value);

    int tuple3[] = {7, 256};
    len = sizeof(tuple3) / sizeof(tuple3[0]);
    float_value = tuple_to_float(tuple3, len);
    printf("%.4f\n", float_value);

    return 0;
}