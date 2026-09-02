#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double tuple_to_float(const int *tuple, size_t len) {
    if (len == 0) return 0.0;
    if (len == 1) return (double)tuple[0];
    
    double result = 0.0;
    for (size_t i = 0; i < len; ++i) {
        result += (double)tuple[i] * pow(10, (len - i - 1));
    }
    return result / pow(10, len - 1);
}

int main() {
    int tuple[] = {3, 1, 4, 1, 5};
    size_t len = sizeof(tuple) / sizeof(tuple[0]);
    
    double result = tuple_to_float(tuple, len);
    printf("The float value is: %f\n", result);
    
    return 0;
}