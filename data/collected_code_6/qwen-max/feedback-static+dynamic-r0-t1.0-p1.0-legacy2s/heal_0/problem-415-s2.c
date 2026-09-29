#include <stdio.h>
#include <limits.h>

void findMaxProductPair(int arr[], int n, int *first, int *second) {
    if (n < 2) return;
    
    int max1 = INT_MIN, max2 = INT_MIN;
    int min1 = INT_MAX, min2 = INT_MAX;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] > max1) {
            max2 = max1;
            max1 = arr[i];
        } else if (arr[i] > max2) {
            max2 = arr[i];
        }
        
        if (arr[i] < min1) {
            min2 = min1;
            min1 = arr[i];
        } else if (arr[i] < min2) {
            min2 = arr[i];
        }
    }
    
    if (max1 * max2 > min1 * min2) {
        *first = max1;
        *second = max2;
    } else {
        *first = min1;
        *second = min2;
    }
}

int main() {
    int arr[] = {1, 4, 3, 6, 7, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    int first, second;
    
    findMaxProductPair(arr, n, &first, &second);
    
    printf("The pair with the highest product is: %d and %d\n", first, second);
    
    return 0;
}