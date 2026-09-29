#include <stdio.h>
#include <stdlib.h>

void findTripletWithSum(const int arr[], int n, int target) {
    int *temp = (int *)malloc(n * sizeof(int));
    if (temp == NULL) {
        return;
    }
    
    for (int i = 0; i < n; i++) {
        temp[i] = arr[i];
    }
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                int swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }
    
    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && temp[i] == temp[i - 1]) continue;
        
        int left = i + 1;
        int right = n - 1;
        int remaining = target - temp[i];
        
        while (left < right) {
            int sum = temp[left] + temp[right];
            
            if (sum == remaining) {
                printf("%d %d %d\n", temp[i], temp[left], temp[right]);
                left++;
                right--;
                
                while (left < right && temp[left] == temp[left - 1]) left++;
                while (left < right && temp[right] == temp[right + 1]) right--;
            }
            else if (sum < remaining) {
                left++;
            }
            else {
                right--;
            }
        }
    }
    
    free(temp);
}

int main() {
    int arr[] = {12, 3, 4, 1, 6, 9, 5, 7, -2, -5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 0;
    
    findTripletWithSum(arr, n, target);
    
    return 0;
}