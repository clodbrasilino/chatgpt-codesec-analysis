#include <stdio.h>

double findNegativeRatio(int arr[], int size) {
    int i, count = 0;
    
    if (size <= 0) 
        return 0;

    for(i = 0; i < size; i++) {
        if(arr[i] < 0)
            count++;
    }
        
    return (double)count/(double)size;
}

int main() {
    int arr[] = {-3, -2, 0, 5, -7, 8, -9};
    int size = sizeof(arr)/sizeof(arr[0]);
    
    printf("The ratio of negative numbers is: %.2lf\n", findNegativeRatio(arr, size));
    return 0;
}