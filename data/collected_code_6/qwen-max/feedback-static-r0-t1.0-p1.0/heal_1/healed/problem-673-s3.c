#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int concatenateIntegers(const int *numbers, size_t count) {
    long result = 0;
    for (size_t i = 0; i < count; ++i) {
        int num = numbers[i];
        int length = 0;
        long temp = num;
        if (temp == 0) {
            length = 1;
        } else {
            while (temp > 0) {
                temp /= 10;
                length++;
            }
        }
        result *= (length ? pow(10, length) : 1);
        result += num;
    }
    return (int)result;
}

int main() {
    int numbers[] = {123, 456, 789};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int result = concatenateIntegers(numbers, count);
    printf("%d\n", result);
    return 0;
}