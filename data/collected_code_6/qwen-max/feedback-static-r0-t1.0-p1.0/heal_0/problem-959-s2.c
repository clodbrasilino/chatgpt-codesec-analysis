#include <stdio.h>
#include <stdlib.h>

double calculate_average(int *numbers, int size) {
    if (size <= 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += numbers[i];
    }
    return sum / size;
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    double avg = calculate_average(numbers, size);
    printf("Average: %.2f\n", avg);
    return 0;
}