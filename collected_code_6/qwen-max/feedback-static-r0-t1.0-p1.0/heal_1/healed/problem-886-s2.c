#include <stdio.h>
#include <stdlib.h>

double average(const int *list, size_t length) {
    if (length == 0) return 0.0;
    double sum = 0.0;
    for (size_t i = 0; i < length; i++) {
        sum += list[i];
    }
    return sum / length;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    double avg = average(numbers, length);
    printf("Average: %.2f\n", avg);
    return 0;
}