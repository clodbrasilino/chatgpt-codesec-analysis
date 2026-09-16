#include <stdio.h>
#include <stdlib.h>

double average(const int *list, size_t length, int *status)
{
    double sum = 0.0;
    size_t i;

    if (list == NULL || length == 0 || status == NULL) {
        if (status != NULL) {
            *status = -1;
        }
        return 0.0;
    }

    for (i = 0; i < length; i++) {
        sum += (double)list[i];
    }

    *status = 0;
    return sum / (double)length;
}

int main(void)
{
    int numbers[] = {10, 20, 30, 40, 50};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    int status = 0;
    double result;

    result = average(numbers, length, &status);

    if (status != 0) {
        fprintf(stderr, "Error: invalid input to average function\n");
        return EXIT_FAILURE;
    }

    if (printf("Average: %f\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}