#include <stdio.h>

int findFirstOccurence(int arr[], int n, int target){
    int start = 0, end = n-1;

    while (start <= end){
        int mid = start + (end - start) / 2;

        if (arr[mid] == target){
            if(mid == 0 || arr[mid - 1] != target){
                return mid;
            }
            end = mid - 1;
        }
        else if (arr[mid] < target){
            start = mid + 1;
        }
        else{
            end = mid -1;
        }
    }
    return -1;
}

int main(){
    int arr[] = {1, 2, 3, 3, 4, 5, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    int target = 3;
    
    int result = findFirstOccurence(arr, n, target);

    if(result != -1){
        printf("First occurrence of %d is at index %d\n", target, result);
    }
    else{
        printf("%d is not present in array\n", target);
    }
    return 0;
}