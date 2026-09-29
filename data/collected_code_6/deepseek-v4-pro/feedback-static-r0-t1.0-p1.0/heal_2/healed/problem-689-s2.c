#include <stdio.h>
#include <limits.h>

int min_jumps(const int arr[], int n) {
    if (n <= 1) {
        return 0;
    }
    
    if (arr[0] == 0) {
        return -1;
    }
    
    int max_reach = arr[0];
    int steps = arr[0];
    int jumps = 1;
    
    for (int i = 1; i < n; i++) {
        if (i == n - 1) {
            return jumps;
        }
        
        if (i + arr[i] > max_reach) {
            max_reach = i + arr[i];
        }
        
        steps--;
        
        if (steps == 0) {
            jumps++;
            
            if (i >= max_reach) {
                return -1;
            }
            
            steps = max_reach - i;
        }
    }
    
    return -1;
}

int main(void) {
    int arr[] = {2, 3, 1, 1, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int result = min_jumps(arr, n);
    
    if (result == -1) {
        printf("Cannot reach the end\n");
    } else {
        printf("Minimum jumps: %d\n", result);
    }
    
    int arr2[] = {1, 0, 1, 1, 4};
    n = sizeof(arr2) / sizeof(arr2[0]);
    result = min_jumps(arr2, n);
    
    if (result == -1) {
        printf("Cannot reach the end\n");
    } else {
        printf("Minimum jumps: %d\n", result);
    }
    
    int arr3[] = {0};
    n = sizeof(arr3) / sizeof(arr3[0]);
    result = min_jumps(arr3, n);
    
    printf("Minimum jumps: %d\n", result);
    
    return 0;
}