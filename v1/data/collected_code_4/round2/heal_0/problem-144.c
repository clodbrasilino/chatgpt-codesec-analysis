#include<stdio.h>
#include<stdlib.h>

// function to calculate sum of all diffferences
int sumOfDifferences(int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            sum += abs(arr[i] - arr[j]);
        }
    }
    return sum;
}

int main(){
    int n;
    printf("Enter the size of the array:\n");
    scanf("%d", &n);
    if(n > 0){
        int *arr = calloc(n, sizeof(int));
        if(arr != NULL){
            printf("Enter the elements of the array:\n");
            for(int i=0; i<n; i++){
                scanf("%d", &arr[i]);
            }
            printf("Sum of absolute differences in all pairs of the given array is %d\n", sumOfDifferences(arr, n));
            free(arr);
        }else{
            printf("Failed to allocate memory.\n");
        }
    }else{
        printf("Size of the array should be greater than zero.\n");
    }
    return 0;
}