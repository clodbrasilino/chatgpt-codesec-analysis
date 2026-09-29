#include<stdio.h>

int findEquilibriumIndex(const int arr[], int size) {
    int leftSum = 0;
    int rightSum = 0;

    for (int i = 0; i < size; i++) {
        rightSum += arr[i];
    }

    for (int i = 0; i < size; i++) {
        rightSum -= arr[i];

        if (leftSum == rightSum) {
            return i;
        }

        leftSum += arr[i];
    }

    return -1;
}

int main() {
    const int arr[] = { -7, 1, 5, 2, -4, 3, 0 };
    int size = sizeof(arr) / sizeof(arr[0]);

    int equilibriumIndex = findEquilibriumIndex(arr, size);

    printf("Equilibrium index is %d\n", equilibriumIndex);

    return 0;
}