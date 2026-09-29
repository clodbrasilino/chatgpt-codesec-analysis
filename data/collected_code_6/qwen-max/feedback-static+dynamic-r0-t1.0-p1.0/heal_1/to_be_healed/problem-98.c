#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
double multiply_and_divide_by_length(int *list, int length) {
    if (length == 0) return 0.0;
    double product = 1.0;
    for (int i = 0; i < length; ++i) {
        product *= list[i];
    }
    return product / length;
}

int main() {
    int numbers[] = {2, 3, 4, 5};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    double result = multiply_and_divide_by_length(numbers, length);
    printf("Result: %f\n", result);
    return 0;
}