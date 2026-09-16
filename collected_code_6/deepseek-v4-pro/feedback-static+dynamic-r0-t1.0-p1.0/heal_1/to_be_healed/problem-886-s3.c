#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'numbers' can be declared as pointer to const [constParameterPointer]
 */
double calculate_average(int *numbers, int length) {
    if (numbers == NULL || length <= 0) {
        return 0.0;
    }
    
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += numbers[i];
    }
    
    return (double)sum / length;
}

int main(void) {
    int numbers[] = {10, 20, 30, 40, 50};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    
    double average = calculate_average(numbers, length);
    printf("Average: %.2f\n", average);
    
    return 0;
}