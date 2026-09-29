#include <stdio.h>
#include <stdbool.h>

bool areArraysEqual(int arr1[], int arr2[], int n, int m) {
    if (n != m)
        return false;

    for (int i = 0; i < n; i++)
        if (arr1[i] != arr2[i])
            return false;

    return true;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr1) / sizeof(int);
    int m = sizeof(arr2) / sizeof(int);

    if (areArraysEqual(arr1, arr2, n, m))
        printf("The arrays are equal.\n");
    else
        printf("The arrays are not equal.\n");

    return 0;
}