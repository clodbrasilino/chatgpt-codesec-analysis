#include <stdio.h>

double positiveRatio(const int arr[], int size) {
    if (size <= 0) return 0.0;
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] > 0) {
            ++count;
        }
    }
    return (double)count / size;
}

int main() {
    int numbers[] = {1, -2, 3, 4, -5, 6, 0, -1};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    double ratio = positiveRatio(numbers, size);
    printf("The ratio of positive numbers: %.2f\n", ratio);
    return 0;
}