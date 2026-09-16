#include <stdio.h>
#include <stdlib.h>

double average(const int *list, size_t length, int *error)
{
    double sum = 0.0;
    size_t i;

    if (list == NULL || length == 0U || error == NULL) {
        if (error != NULL) {
            *error = 1;
        }
        return 0.0;
    }

    for (i = 0U; i < length; i++) {
        sum += (double)list[i];
    }

    *error = 0;
    return sum / (double)length;
}

int main(void)
{
    int numbers[] = { 4, 8, 15, 16, 23, 42 };
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    int error = 0;
    double result;

    result = average(numbers, length, &error);
    if (error != 0) {
        if (fprintf(stderr, "Error: invalid input to average function\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Average: %f\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}