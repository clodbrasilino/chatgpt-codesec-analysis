#include <stdio.h>

void findHighestProductPair(const int arr[], int n) {
    if (n < 2) {
        printf("Array must have at least 2 elements\n");
        return;
    }

    int max1 = arr[0], max2 = arr[1];
    int min1 = arr[0], min2 = arr[1];

    for (int i = 2; i < n; i++) {
        if (arr[i] > max1) {
            max2 = max1;
            max1 = arr[i];
        } 
        else if (arr[i] > max2) {
            max2 = arr[i];
        }

        if (arr[i] < min1) {
            min2 = min1;
            min1 = arr[i];
        } 
        else if (arr[i] < min2) {
            min2 = arr[i];
        }
    }
    
    int product1 = min1 * min2;
    int product2 = max1 * max2;
    
    if (product1 > product2) {
        printf("Pair with highest product: %d and %d\n", min1, min2);
    } 
    else {
        printf("Pair with highest product: %d and %d\n", max1, max2);
    }
}

int main() {
    int arr[] = {1, -4, 3, 6, 7, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    findHighestProductPair(arr, n);
    return 0;
}