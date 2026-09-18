#include <stdio.h>

int findLastPosition(int* array, int len, int target) {
    int start = 0;
    int end = len - 1;
    int result = -1;

    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (target == array[mid]) {
            result = mid;
            start = mid + 1;
        }
        else if (target < array[mid])
            end = mid - 1;
        else
            start = mid + 1;
    }

    return result;
}

int main() {
    int array[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int len = sizeof(array) / sizeof(array[0]);
    int target = 3;
    int result = findLastPosition(array, len, target);
    if (result != -1)
        printf("Last position of %d is %d\n", target, result);
    else
        printf("%d is not present in array\n", target);
    return 0;
}