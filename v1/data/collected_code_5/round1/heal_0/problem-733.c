#include <stdio.h>

int firstOccurrence(int arr[], int n, int x) {
    int start = 0;
    int end = n-1;

    while(start <= end){
        int mid = (start + end) / 2;

        if(arr[mid] < x){
            start = mid + 1;
        }
        else if(arr[mid] > x){
            end = mid - 1;
        }
        else{
            if(mid == 0 || arr[mid-1] != arr[mid]){
                return mid;
            }else{
                end = mid - 1;
            }
        }
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 2, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(int);
    int x = 2;

    printf("%d", firstOccurrence(arr, n, x));
    return 0;
}