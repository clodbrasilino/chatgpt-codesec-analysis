#include <stdio.h>
#include <limits.h>

int find_largest_negative(int arr[], int n) {
    int max_negative = INT_MIN;
    int flag = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            flag = 1;
            if (arr[i] > max_negative) {
                max_negative = arr[i];
            }
        }
    }
    
    if(flag==0)
      return 0; 
    else
      return max_negative;
}

int main() {
    int arr[] = {-1, -3, -4, -2, 0, 1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int largest_negative = find_largest_negative(arr, n);
   
    if(largest_negative != 0)
       printf("Largest negative number is %d\n", largest_negative);
    else
       printf("No negative number in the array\n");

    return 0;
}