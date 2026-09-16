#include <stdio.h>
#include <stdlib.h>

double find_average(const double *list, size_t size) {
    if (list == NULL || size == 0) {
        return 0.0;
    }

    double sum = 0.0;
    for (size_t i = 0; i < size; ++i) {
        sum += list[i];
    }

    return sum / size;
}

int main(void) {
    double numbers[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    double avg = find_average(numbers, count);
    printf("%f\n", avg);

    return 0;
}