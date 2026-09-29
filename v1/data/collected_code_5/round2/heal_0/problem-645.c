#include <stdio.h>

int findProduct(int rows, int cols, int arr[rows][cols], int k) {
    if(k < 0 || k >= cols) {
        printf("Kth index out of range");
        return -1;
    }
    int product = 1;
    for(int i = 0; i < rows; i++) {
        product *= arr[i][k];
    }
    return product;
}

int main() {
    int rows, cols, k;
    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter the number of columns: ");
    scanf("%d", &cols);
    int arr[rows][cols];
    printf("Enter the elements of the array: ");
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    printf("Enter the kth index: ");
    scanf("%d", &k);
    int product = findProduct(rows, cols, arr, k);
    if(product != -1) {
        printf("The product of the kth  index is: %d", product);
    }
    return 0;
}