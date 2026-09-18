#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int getMaximumSum(int arr[], int n, int k) {
    int i = 0, sum = 0;
    qsort(arr, n, sizeof(arr[0]), compare);

    while(i < n-1 && k > 0) {
        sum += arr[i] + arr[i+1];
        i += 2;
        k--;
    }
    return sum;
}

int main() {
    int n, k;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    printf("Enter the number of pairs: ");
    scanf("%d", &k);
    int i, arr[n];
    printf("Enter array elements: \n");
    for(i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }
    int result = getMaximumSum(arr, n, k);
    printf("Maximum sum is: %d\n", result);
    return 0;
}