#include <stdio.h>
#include <stdlib.h>

double multiply_and_divide(const int *list, size_t length) {
    if (list == NULL || length == 0) {
        return 0.0;
    }

    double product = 1.0;
    for (size_t i = 0; i < length; i++) {
        product *= list[i];
    }

    return product / length;
}

int main(void) {
    int list[] = {2, 4, 6, 8, 10};
    size_t length = sizeof(list) / sizeof(list[0]);

    double result = multiply_and_divide(list, length);
    printf("%f\n", result);

    return 0;
}