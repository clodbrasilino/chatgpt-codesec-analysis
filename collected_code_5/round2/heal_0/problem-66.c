#include <stdio.h>

int count_positive(int arr[], int n) {
    int count = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] > 0){
            count++;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, -2, 3, -4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    int count = count_positive(arr, n);
    printf("Number of positive numbers: %d\n", count);
    return 0;
}