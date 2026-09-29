/* Possible weaknesses found:
 *  stray '`' in program
 */
```
#include <stdio.h>

int minSwaps(int arr[], int n)
{
    int countZeros = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] == 0)
            countZeros++;
    }

    int maxCount = 0, currCount = 0;

    for(int i = 0; i < n; i++){
        if(arr[i] == 1) 
            currCount++;
        else
            currCount=0;
        
        if(currCount > maxCount)
            maxCount = currCount;
    }

    return (countZeros - maxCount);
}

int main(){
    int arr[] = {1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("The minimal swaps required to sort the array: %d", minSwaps(arr, size));
    return 0;
}