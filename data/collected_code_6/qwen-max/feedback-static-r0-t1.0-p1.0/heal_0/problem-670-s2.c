#include <stdio.h>
#include <stdbool.h>

bool is_decreasing(int *arr, int length) {
    if (length <= 1) {
        return false;
    }
    for (int i = 1; i < length; ++i) {
        if (arr[i - 1] <= arr[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {5, 4, 3, 2, 1};
    int length = sizeof(arr) / sizeof(arr[0]);
    bool result = is_decreasing(arr, length);
    if (result) {
        printf("The sequence is decreasing.\n");
    } else {
        printf("The sequence is not decreasing.\n");
    }
    return 0;
}