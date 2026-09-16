#include <stdio.h>

int findEquilibriumIndex(const int arr[], int n) {
    if (n == 0) return -1;
    int leftSum = 0, rightSum = 0;
    for (int i = 0; i < n; i++) {
        rightSum += arr[i];
    }
    for (int i = 0; i < n; i++) {
        rightSum -= arr[i];
        if (leftSum == rightSum) {
            return i;
        }
        leftSum += arr[i];
    }
    return -1;
}

int main() {
    const int arr[] = {-7, 1, 5, 2, -4, 3, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    int index = findEquilibriumIndex(arr, n);
    if (index != -1) {
        printf("Equilibrium index is %d\n", index);
    } else {
        printf("No equilibrium index found\n");
    }
    return 0;
}