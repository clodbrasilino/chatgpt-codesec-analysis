#include <stdbool.h>
#include <stdio.h>

bool isMonotonic(int* nums, int numsSize) {
    bool increasing = true;
    bool decreasing = true;

    for (int i = 0; i < numsSize - 1; ++i) {
        if (nums[i] > nums[i+1])
            increasing = false;
        if (nums[i] < nums[i+1])
            decreasing = false;
    }

    return increasing || decreasing;
}

int main() {
    int arr1[] = {1, 2, 3, 4};
    int arr2[] = {4, 3, 2, 1};
    int arr3[] = {1, 2, 3, 2};

    printf("%s\n", isMonotonic(arr1, 4) ? "True" : "False");
    printf("%s\n", isMonotonic(arr2, 4) ? "True" : "False");
    printf("%s\n", isMonotonic(arr3, 4) ? "True" : "False");

    return 0;
}