#include <stdio.h>

int findKthElement(int arr[], int n, int k) {
    int oddCount = 0;
    for(int i = 0; i < n; i++) {
        if(arr[i] % 2 != 0) {
            oddCount++;
        }
    }
    if(k <= oddCount) {
        return arr[k - 1];
    } else {
        return arr[oddCount + k - 1];
    }
}

int main() {
    int arr[] = {1, 3, 5, 2, 4, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    printf("The %dth element is %d\n", k, findKthElement(arr, n, k));
    return 0;
}