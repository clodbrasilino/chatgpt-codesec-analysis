#include <stdio.h>

int sumNonRepeated(int arr[], int n) {
    int sum = 0;
    int i, j, count;

    for (i=0; i<n; i++) {
        count = 0;
        for (j=0; j<n; j++) {
            if (arr[i] == arr[j])
                count++;
            if (count > 1)
                break;
        }
        if (count == 1)
            sum += arr[i];
    }

    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Sum of non-repeated elements is: %d", sumNonRepeated(arr, n));
    
    return 0;
}