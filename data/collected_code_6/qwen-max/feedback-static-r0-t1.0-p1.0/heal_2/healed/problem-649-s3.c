#include <stdio.h>
#include <stdlib.h>

int sum_range(const int *numbers, int start, int end) {
    if (numbers == NULL || start > end) {
        return 0;
    }
    int sum = 0;
    for (int i = start; i <= end; ++i) {
        sum += numbers[i];
    }
    return sum;
}

int main() {
    const int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int result = sum_range(arr, 2, 5);
    printf("Sum: %d\n", result);
    return 0;
}