#include <stdio.h>

double find_average(const int list[], int size) {
    if (list == NULL || size <= 0) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += list[i];
    }
    
    return sum / size;
}

int main(void) {
    int numbers[] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    double average = find_average(numbers, size);
    printf("Average: %.2f\n", average);
    
    return 0;
}