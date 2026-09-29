#include <stdio.h>
#include <stdbool.h>

bool canSortCornerElements(int* arr, int n) {
    if(n <= 1)
        return true;

    int start = 0;
    int end = n - 1;

    while(start < end){
        if(arr[start] > arr[start + 1] || arr[end] < arr[end - 1])
            return false;

        start += 1;
        end -= 1;
    }
    return true;
}

int main() {
    int arr[] = {1, 3, 2, 4};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("%s\n", canSortCornerElements(arr, n) ? "Array can be sorted using corner elements" : "Array cannot be sorted using corner elements");

    return 0;
}