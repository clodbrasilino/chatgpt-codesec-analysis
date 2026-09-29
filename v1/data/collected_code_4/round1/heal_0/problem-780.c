#include<stdio.h>
#include<stdlib.h>

#define SIZE 100

void findCombinations(int arr[], int n, int sum, int start, int data[], int index) {
    if(sum < 0){
        return;
    }
    if(sum == 0) {
        for(int i=0; i<index; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
        return;
    }
    for(int i=start; i<n; i++) {
        data[index] = arr[i];
        findCombinations(arr, n, sum - arr[i], i, data, index + 1);
    }
}

int main() {
    int arr[SIZE], data[SIZE], n, sum;
    printf("Enter the number of elements in array: ");
    scanf("%d", &n);
    printf("Enter the array elements: ");
    for(int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter the sum: ");
    scanf("%d", &sum);
    findCombinations(arr, n, sum, 0, data, 0);
    return 0;
}