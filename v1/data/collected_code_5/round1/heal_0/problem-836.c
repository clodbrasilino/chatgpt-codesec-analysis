#include <stdio.h>
#include <limits.h>

int findMaxSubArray(int arr[], int n) {
    int curr_sum = 0;
    int max_sum = INT_MIN;
    int start = 0;
    int end = 0;
    int temp = 0;

    for(int i = 0; i < n; i++) {
        curr_sum += arr[i];

        if (max_sum < curr_sum){
            max_sum = curr_sum;
            start = temp;
            end = i;
        }

        if (curr_sum < 0){
            curr_sum = 0;
            temp = i+1;
        }
    }
    return (end - start + 1);
}

int main() {
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(arr) / sizeof(arr[0]);

    int length = findMaxSubArray(arr, n);
    printf("Length of the subarray having maximum sum is %d\n", length);
    return 0;
}