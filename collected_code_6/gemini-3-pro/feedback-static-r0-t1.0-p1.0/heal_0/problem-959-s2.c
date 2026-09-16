#include <stdio.h>
#include <stdlib.h>

double calculate_average(const int *array, size_t length) {
    if (array == NULL || length == 0) {
        return 0.0;
    }

    long long sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += array[i];
    }

    return (double)sum / (double)length;
}

int main(void) {
    size_t length = 5;
    int *numbers = (int *)malloc(length * sizeof(int));
    
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    numbers[0] = 10;
    numbers[1] = 20;
    numbers[2] = 30;
    numbers[3] = 40;
    numbers[4] = 50;

    double average = calculate_average(numbers, length);
    printf("Average: %.2f\n", average);

    free(numbers);
    numbers = NULL;

    return EXIT_SUCCESS;
}