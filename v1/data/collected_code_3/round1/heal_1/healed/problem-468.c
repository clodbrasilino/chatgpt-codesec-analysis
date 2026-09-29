#include <stdio.h>
#include <stdlib.h>

int maxProductIS(int arr[], int n) {
    int *max_product = (int*) malloc(n * sizeof(int));
    if (max_product == NULL) { 
        return -1;  
    }
  
    int max = 1;

    for (int i = 0; i < n; i++)
        max_product[i] = arr[i];

    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (arr[i] > arr[j] && max_product[i] < max_product[j] * arr[i])
                max_product[i] = max_product[j] * arr[i];

    for (int i = 0; i < n; i++)
        if (max < max_product[i])
            max = max_product[i];

    free(max_product);

    return max;
}

int main() {
    int arr[] = {3, 100, 4, 5, 150, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    int maxProduct = maxProductIS(arr, n);
    
    if (maxProduct == -1) {
        printf("Memory allocation failed");
        return -1;
    }
    
    printf("Maximum product of increasing subsequence is %d\n", maxProduct);

    return 0;
}