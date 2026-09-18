#include <stdio.h>

int addMinToMakeSumEven(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];

    return ((sum % 2 == 0) ? 0 : 1);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("%d\n", addMinToMakeSumEven(arr, n));

    return 0;
}