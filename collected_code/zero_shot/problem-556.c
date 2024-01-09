#include <stdio.h>

int countOddXORPairs(int arr[], int n) {
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((arr[i] ^ arr[j]) % 2 == 1)
                count++;
        }
    }
    
    return count;
}

int main() {
    int n;
    printf("Enter the size of array: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter the elements of array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int result = countOddXORPairs(arr, n);
    
    printf("Number of pairs with XOR as an odd number: %d\n", result);
    
    return 0;
}