#include <stdio.h>

double arithmeticAverage(int* list, int size) {
    double product = 1.0;

    for(int i=0; i<size; i++)
    {
        if(list[i] == 0) {
            return 0;
        }

        product *= list[i];
    }

    return product / size;
}

int main() {
    int size;
    printf("\nEnter the number of elements : ");
    scanf("%d", &size);
    
    int arr[size];

    printf("\nInput the array elements : ");
    for(int i = 0; i < size; i++){
        scanf("%d", &arr[i]);
    }

    double result = arithmeticAverage(arr, size);

    printf("\nResult : %lf", result);

    return 0;
}