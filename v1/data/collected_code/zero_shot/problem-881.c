#include <stdio.h>

void findSum(int arr[], int size) {
    int sumEven = 0;
    int sumOdd = 0;
    int evenCount = 0;
    int oddCount = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            sumEven += arr[i];
            evenCount++;
        } else {
            sumOdd += arr[i];
            oddCount++;
        }
        
        if (evenCount == 1 && oddCount == 1) {
            break;
        }
    }
    
    printf("Sum of first even number: %d\n", sumEven);
    printf("Sum of first odd number: %d\n", sumOdd);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    findSum(arr, size);
    
    return 0;
}