#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>

/* Possible weaknesses found:
 *  Parameter 'numbers' can be declared as const array [constParameter]
 */
void process_numbers(double numbers[], size_t length) {
    if (numbers == NULL || length == 0) {
        fprintf(stderr, "Invalid input\n");
        return;
    }

    double sum = 0.0;
    for (size_t i = 0; i < length; i++) {
        errno = 0;
        double rounded = round(numbers[i]);
        if (errno != 0) {
            fprintf(stderr, "Rounding error at index %zu\n", i);
            return;
        }
        sum += rounded;
    }

    double result = sum * (double)length;
    printf("%.2f\n", result);
}

int main(void) {
    double numbers[] = {1.4, 2.6, 3.5, 4.2, 5.8};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    
    process_numbers(numbers, length);
    
    return 0;
}