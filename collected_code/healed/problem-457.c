#include <stdio.h>
#include <limits.h>

void findMinLength(const int arr[], int n) {
    int minLen = INT_MAX;
    int startPos = -1;
    
    for(int i = 0; i < n; i++) {
        int len = 0;   
        
        for(int j = i; j < n; j++) {
            len++;  
            
            if(len < minLen) {
                minLen = len;
                startPos = i;
            }
        }
    }
    
    printf("Sublist with minimum length: ");
    for(int i = startPos; i < startPos + minLen; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {
    const int arr[] = {3, 2, 7, 1, 5, 4, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    findMinLength(arr, n);
    
    return 0;
}