#include <stdio.h>
#include <math.h>

int round_and_sum(const double *numbers, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        int rounded = (int)round(numbers[i]);
        sum += rounded * rounded * rounded;
    }
    return sum;
}

int main() {
    double numbers[] = {12.5, 13.3, 14.7, 15.2};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int result = round_and_sum(numbers, length);
    printf("%d\n", result);
    return 0;
}