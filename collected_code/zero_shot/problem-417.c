#include <stdio.h>

int findCommonElement(int arr[][2], int n) {
    int common = arr[0][0];
    int count;
    
    for (int i = 0; i < n; i++) {
        count = 0;
        
        for (int j = 0; j < n; j++) {
            if (arr[i][0] == arr[j][0]) {
                count++;
            }
        }
        
        if (count == n) {
            common = arr[i][0];
            break;
        }
    }
    
    return common;
}

int main() {
    int arr[][2] = {{1, 10}, {2, 20}, {3, 30}, {1, 40}};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int common = findCommonElement(arr, n);
    
    printf("The common first element is: %d", common);
    
    return 0;
}