#include <stdio.h>
#include <math.h>

void nthPower(int arr[], int size, int n) {
    for (int i = 0; i < size; i++) {
        arr[i] = pow(arr[i], n);
    }
}

int main() {
    int size, n;
    printf("Enter the size of the list: ");
    scanf("%d", &size);

    if(size<=0){
        printf("Invalid size, please enter a positive number\n");
        return 0;
    }
    
    int arr[size];
    printf("Enter the elements of the list: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the power to raise each element: ");
    scanf("%d", &n);

    nthPower(arr, size, n);

    printf("List after raising each element to the %d-th power:\n", n);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}