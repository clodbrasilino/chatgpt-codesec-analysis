#include <stdio.h>

int countOddXORPairs(const int arr[], const int n) {
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
    if(scanf("%d", &n) != 1){ 
        printf("Failed to read integer.\n");
        return 1; 
    }
    
    int arr[n];
    printf("Enter the elements of array: ");
    for (int i = 0; i < n; i++) {
        if(scanf("%d", &arr[i]) != 1){
            printf("Failed to read array element.\n");
            return 1;
        }
    }

    int result = countOddXORPairs(arr, n);

    printf("Number of pairs with XOR as an odd number: %d\n", result);

    return 0;
}