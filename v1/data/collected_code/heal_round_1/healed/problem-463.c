#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int maxProductSubarray(int arr[], int n) {
    int max_ending_here = 1;
    int min_ending_here = 1;
    int max_so_far = 1;
 
    for (int i = 0; i < n; i++) {
        if(arr[i] > 0) {
            max_ending_here = max_ending_here * arr[i];
            min_ending_here = min(min_ending_here * arr[i], 1);
        } else if(arr[i] == 0) {
            max_ending_here = 1;
            min_ending_here = 1;
        } else {
            int temp = max_ending_here;
            max_ending_here = max(min_ending_here * arr[i], 1);
            min_ending_here = temp * arr[i];
        }

        if(max_so_far < max_ending_here){
            max_so_far = max_ending_here;
        }
   }

    return max_so_far;
}

int main() {
    int arr[] = {2, -3, 1, -2, 0, 9, -4};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum product subarray is %d\n", maxProductSubarray(arr, n));
    return 0;
}