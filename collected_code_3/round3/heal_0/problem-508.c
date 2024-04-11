#include <stdio.h>
#include <stdbool.h>

bool checkOrder(int arr1[], int arr2[], int m, int n) {
    int i = 0, j = 0;
    while (i < m && j < n) {
        if (arr1[i] == arr2[j]) {
            i++;
            j++;
        } else {
            j++;
        }
    }
    return (i == m);
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {2, 1, 3, 5, 4};
    int m = sizeof(arr1) / sizeof(arr1[0]);
    int n = sizeof(arr2) / sizeof(arr2[0]);
    if (checkOrder(arr1, arr2, m, n)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}