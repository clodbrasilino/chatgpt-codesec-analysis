#include <stdio.h>
#include <math.h>

int roundListAndMultiplyLength(const int *arr, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += round(arr[i]);
    }
    return sum * len;
}

int main() {
    double numbers[] = {1.6, 2.4, 3.5, 4.5};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int rounded_numbers[length];
    for (int i = 0; i < length; i++) {
        rounded_numbers[i] = (int)round(numbers[i]);
    }
    printf("%d\n", roundListAndMultiplyLength(rounded_numbers, length));
    return 0;
}