#include <stdlib.h>
#include <stdio.h>

void fillSpiral(int n, int arr[n][n]){ 
    int value = 1;
    int low = 0, high = n - 1;
    while(value <= n*n)
    { 
        for(int i = low; i <= high && value <= n*n; i++)
            arr[low][i] = value++;
        for(int i = low + 1; i <= high && value <= n*n; i++)
            arr[i][high] = value++;
        for(int i = high - 1; i >= low && value <= n*n; i--)
            arr[high][i] = value++;
        for(int i = high - 1; i > low && value <= n*n; i--)
            arr[i][low] = value++;
        
        low++, high--; 
    }
} 

void printMatrix(int n, int arr[n][n]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            printf("%2d ", arr[i][j]);
        printf("\n");
    }
}

int main(){
    int n;
    printf("Enter the order of matrix : ");
    scanf("%d",&n);
    
    if(n <= 0){
        printf("Invalid size.\n");
        return 1;
    }
    
    int arr[n][n];
    fillSpiral(n, arr);
    printMatrix(n, arr);
    
    return 0;
}