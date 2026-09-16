#include <stdio.h>

int findEquilibriumIndex(int arr[], int n) {
    int leftSum = 0, rightSum = 0;

    for (int i = 1; i < n; i++) {
        rightSum += arr[i];
    }

    for (int i = 0; i < n; i++) {
        if (leftSum == rightSum) {
            return i;
        }
        if (i + 1 < n) {
            leftSum += arr[i];
            rightSum -= arr[i + 1];
        }
    }

    return -1;
}

int main() {
    int arr[] = {-7, 1, 5, 2, -4, 3, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    int index = findEquilibriumIndex(arr, n);
    if (index != -1) {
        printf("Equilibrium index is: %d\n", index);
    } else {
        printf("No equilibrium index found.\n");
    }
    return 0;
}