#include <stdio.h>

int lastOccurrence(int arr[], int n, int x) {
    int low = 0, high = n - 1;
    int last = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == x) {
            last = mid;
            low = mid + 1;
        }
        else if (arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    
    return last;
}

int main() {
    int arr[] = {1, 2, 3, 3, 4, 5, 5, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 5;
    
    int lastIndex = lastOccurrence(arr, n, x);
    
    printf("Last occurrence of %d is at index %d\n", x, lastIndex);
    
    return 0;
}