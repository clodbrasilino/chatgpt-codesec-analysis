#include <stdbool.h> 
#include <stdio.h> 

bool onlyOneDistinct(int arr[], int length) {
    for (int i = 1; i < length; i++) {
        if (arr[0] != arr[i])
            return false;
    }
    return true;
}

int main(){
    int arr[] = {3, 3, 3, 3};
    int n = sizeof(arr)/sizeof(arr[0]);

    if(onlyOneDistinct(arr, n)){
        printf("Array contains only one distinct element\n");
    }
    else{
        printf("Array contains more than one distinct element\n");
    }
    
    return 0;
}