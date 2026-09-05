#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double calculate(const int *array, size_t length) {
    if (array == NULL || length == 0) {
        return 0.0;
    }

    double sum = 0.0;
    for (size_t i = 0; i < length; i++) {
        sum += round((double)array[i]);
    }

    return sum * length;
}

int main(void) {
    int array[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(array) / sizeof(array[0]);

    double result = calculate(array, length);

    printf("%f\n", result);

    return EXIT_SUCCESS;
}