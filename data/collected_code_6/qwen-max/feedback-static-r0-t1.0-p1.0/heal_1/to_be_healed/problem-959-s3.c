#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
double find_average(int *list, int size) {
    if (size <= 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += list[i];
    }
    return sum / size;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    double average = find_average(numbers, size);
    printf("The average is: %.2f\n", average);
    return 0;
}