#include <stdio.h>
#include <stdlib.h>

double average_of_list(int *list, size_t length) {
    if (list == NULL || length == 0) {
        fprintf(stderr, "Error: invalid input\n");
        exit(EXIT_FAILURE);
    }

    long long sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += list[i];
    }

    return (double)sum / (double)length;
}

int main(void) {
    int numbers[] = {10, 20, 30, 40, 50};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);

    double result = average_of_list(numbers, length);
    printf("Average: %.2f\n", result);

    return 0;
}