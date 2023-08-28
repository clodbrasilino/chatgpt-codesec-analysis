#include<stdio.h>

int findKthElement(int arr[], int n, int k) {
    int oddCount = 0;
    int i = 0;
    
    while (i < n) {
        if (arr[i] % 2 != 0) {
            oddCount++;
            
            if (oddCount == k) {
                return arr[i];
            }
        }
        i++;
    }
    
    i = 0;
    while (i < n) {
        if (arr[i] % 2 == 0) {
            oddCount++;
            
            if (oddCount == k) {
                return arr[i];
            }
        }
        i++;
    }
    
    return -1; // If k is out of range
}

int main() {
    int arr[] = {3, 9, 2, 7, 6, 4, 1, 8, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int k;
    printf("Enter the value of k: ");
    scanf("%d", &k);
    
    int kthElement = findKthElement(arr, n, k);
    
    if (kthElement == -1) {
        printf("Invalid k! Element not found.");
    } else {
        printf("The kth element is: %d", kthElement);
    }
    
    return 0;
}