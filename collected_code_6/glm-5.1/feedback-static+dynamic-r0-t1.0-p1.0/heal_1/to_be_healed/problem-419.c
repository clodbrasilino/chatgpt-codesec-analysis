#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
double calculate(int *array, size_t length) {
    if (array == NULL || length == 0) {
        return 0.0;
    }

    double sum = 0.0;
    size_t i;
    for (i = 0; i < length; i++) {
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