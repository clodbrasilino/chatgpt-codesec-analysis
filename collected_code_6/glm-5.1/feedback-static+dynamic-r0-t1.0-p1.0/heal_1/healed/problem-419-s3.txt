#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int calculate_rounded_sum(const double *numbers, size_t length) {
    if (numbers == NULL || length == 0) {
        return 0;
    }

    long long sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += (long long)round(numbers[i]);
    }

    sum *= (long long)length;

    if (sum > INT_MAX || sum < INT_MIN) {
        exit(EXIT_FAILURE);
    }

    return (int)sum;
}

int main(void) {
    double numbers[] = {1.2, 2.5, 3.7, 4.0, -1.2};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);

    int result = calculate_rounded_sum(numbers, length);
    printf("%d\n", result);

    return 0;
}