#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'numbers' can be declared as pointer to const [constParameterPointer]
 */
int sum_negative_numbers(int *numbers, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        if (numbers[i] < 0) {
            sum += numbers[i];
        }
    }
    return sum;
}

int main(int argc, char *argv[]) {
    int numbers[] = {-5, 10, -3, 7, -2, 0, -8};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int result = sum_negative_numbers(numbers, length);
    printf("Sum of negative numbers: %d\n", result);
    return 0;
}