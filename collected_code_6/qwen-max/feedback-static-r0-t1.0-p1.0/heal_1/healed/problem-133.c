#include <stdio.h>
#include <stdlib.h>

int sumNegative(const int *numbers, size_t count) {
    int sum = 0;
    for (size_t i = 0; i < count; ++i) {
        if (numbers[i] < 0) {
            sum += numbers[i];
        }
    }
    return sum;
}

int main() {
    int numbers[] = {1, -2, 3, -4, 5, -6};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int result = sumNegative(numbers, count);
    printf("The sum of negative numbers is: %d\n", result);
    return 0;
}