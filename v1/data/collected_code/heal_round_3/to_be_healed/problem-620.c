#include<stdio.h>
#include<stdlib.h>

void largestDivisibleSubset(int arr[], int n) {
    if (n == 0)
        return;
 
    int count = 1, maxSubsetSize = 1;
    int lastElementIndex = 0;
    int *subsetSize = (int*)malloc(sizeof(int)*n);
    int *previousIndex = (int*)malloc(sizeof(int)*n);

    if(subsetSize == NULL || previousIndex == NULL){
       printf("\nFailure to allocate memory for subsetSize or previousIndex\n");
        if(previousIndex)
            free(previousIndex);
        if(subsetSize)
            free(subsetSize);
        return;
    }

    for (int i = 0; i < n; i++) {
        subsetSize[i] = 1;
        previousIndex[i] = -1;
    }
 
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] % arr[j] == 0 && subsetSize[i] < subsetSize[j] + 1) {
                subsetSize[i] = subsetSize[j] + 1;
                previousIndex[i] = j;
 
                if (subsetSize[i] > maxSubsetSize) {
                    maxSubsetSize = subsetSize[i];
                    lastElementIndex = i;
                }
            }
        }
    }

    int *subset = (int*)malloc(sizeof(int)*maxSubsetSize);

    if(subset == NULL){
        printf("\nFailure to allocate memory for subset\n");
        free(previousIndex);
        free(subsetSize);
        return;
    }

    int currentIndex = lastElementIndex;
    for (int i = maxSubsetSize - 1; i >= 0; i--) {
        subset[i] = arr[currentIndex];
        currentIndex = previousIndex[currentIndex];
    }

    printf("Largest Divisible Subset: ");
    for (int i = 0; i < maxSubsetSize; i++) {
        /* Possible weaknesses found:
         *  use of uninitialized value '*subset_95 + _59' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        printf("%d ", subset[i]);
    }

    free(subsetSize);
    free(previousIndex);
    free(subset);
}

int main() {
    int arr[] = {1, 2, 3, 4, 6, 8, 12};
    size_t n = sizeof(arr)/sizeof(arr[0]);
    
    largestDivisibleSubset(arr, n);
    
    return 0;
}