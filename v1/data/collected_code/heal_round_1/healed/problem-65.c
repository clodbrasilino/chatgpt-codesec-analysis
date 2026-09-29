#include <stdio.h>

int listSum(const int* arr, int size) {
    if (size == 0)
        return 0;
    else
        return arr[size-1] + listSum(arr, size-1);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int sum = listSum(arr, size);
    printf("Sum: %d\n", sum);
    return 0;
}