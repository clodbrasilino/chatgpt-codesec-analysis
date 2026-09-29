#include <stdio.h>

int findElement(int arr[], int size) {
    int ans = arr[0];
    for (int i = 1; i < size; i++) {
        ans ^= arr[i];
    }
    return ans;
}

int main() {
    int arr[] = {1, 1, 2, 2, 3, 4, 4, 5, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = findElement(arr, size);
    
    printf("The element that appears only once is: %d\n", result);
    
    return 0;
}