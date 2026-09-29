#include <stdio.h>
#include <limits.h>

void findMaxProductPair(int arr[], int n, int *maxProductPair) {
    if(n < 2) 
        return;

    int max, secondMax, min, secondMin;
    max = secondMax = INT_MIN;
    min = secondMin = INT_MAX;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            secondMax = max;
            max = arr[i];
        }
        else if (arr[i] > secondMax) {
            secondMax = arr[i];
        }
        
        if (arr[i] < min) {
            secondMin = min;
            min = arr[i];
        }
        else if (arr[i] < secondMin) {
            secondMin = arr[i];
        }
    }  
    
    if ((max * secondMax) > (min * secondMin)) {
        maxProductPair[0] = max;
        maxProductPair[1] = secondMax;
    }
    else {
        maxProductPair[0] = min;
        maxProductPair[1] = secondMin;
    }
}

int main() {
    int arr[] = {1, 4, 3, 6, 7, 0};
    int n = sizeof(arr)/sizeof(arr[0]);
    int maxProductPair[2];

    findMaxProductPair(arr, n, maxProductPair);

    printf("Pair is [%d, %d]", maxProductPair[0], maxProductPair[1]);

    return 0;
}