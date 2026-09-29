#include <stdio.h>
#include <stdlib.h>

int sum_positive(int *numbers, int length) {
    int sum = 0;
    for (int i = 0; i < length; ++i) {
        if (numbers[i] > 0) {
            sum += numbers[i];
        }
    }
    return sum;
}

int main() {
    int nums[] = {-1, 2, -3, 4, 5};
    int length = sizeof(nums) / sizeof(nums[0]);
    int result = sum_positive(nums, length);
    printf("Sum of positive numbers: %d\n", result);
    return 0;
}