#include <stdio.h>
#include <limits.h>

int findThirdLowest(int *nums, int size, int *third) {
    int first = INT_MAX, second = INT_MAX, third_lowest = INT_MAX;
    for (int i = 0; i < size; ++i) {
        if (nums[i] > 0) {
            if (nums[i] < first) {
                third_lowest = second;
                second = first;
                first = nums[i];
            } else if (nums[i] < second && nums[i] != first) {
                third_lowest = second;
                second = nums[i];
            } else if (nums[i] < third_lowest && nums[i] != second && nums[i] != first) {
                third_lowest = nums[i];
            }
        }
    }
    *third = third_lowest;
    return third_lowest != INT_MAX ? 1 : 0;
}

int sumOfThreeLowest(int *nums, int size) {
    int first, second, third, sum = 0;
    if (findThirdLowest(nums, size, &third)) {
        first = second = INT_MAX;
        for (int i = 0; i < size; ++i) {
            if (nums[i] > 0 && (first == INT_MAX || second == INT_MAX)) {
                if (nums[i] < first) {
                    second = first;
                    first = nums[i];
                } else if (nums[i] < second && nums[i] != first) {
                    second = nums[i];
                }
            } else {
                break;
            }
        }
        sum = first + second + third;
    }
    return sum;
}

int main() {
    int arr[] = {4, 2, 3, 1, 6, -3, 5, 0, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    int sum = sumOfThreeLowest(arr, size);
    printf("Sum of the three lowest positive numbers: %d\n", sum);
    return 0;
}