#include <stdio.h>
#define MAX 10000

int sumOfProduct(int* arr, int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        int product = 1;
        for(int j = i; j < n; j++) {
            product *= arr[j];
            sum += product;
        }
    }
    return sum;
}

int main() {
    int size = 0, arr[MAX];
    printf("Enter the size of array: ");
    scanf("%d", &size);

    printf("Enter array elements: ");
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    printf("Sum of all sub-array products is: %d", sumOfProduct(arr, size));
    
    return 0;
}