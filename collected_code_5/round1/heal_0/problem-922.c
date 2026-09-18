#include <stdio.h>
#include <stdlib.h>

void highest_product_pair(int *arr, int size, int *a, int *b) {
    if(size < 2) {
        printf("Invalid input, array should have at least two elements.\n");
        exit(0);
    }

    int max1 = arr[0], max2 = arr[1];
    if(max1 < max2) {
      int temp = max1;
      max1 = max2;
      max2 = temp;
    }

    for(int i = 2; i<size; i++) {
        if(arr[i] > max1) {
            max2 = max1;
            max1 = arr[i];
        } else if(arr[i] > max2) {
            max2 = arr[i];
        }
    }

    *a = max1;
    *b = max2;
}

int main() {
    int arr[] = {1, 20, 3, 4, 5, 6};
    int a, b, arrSize;
    arrSize = sizeof(arr) / sizeof(arr[0]);

    highest_product_pair(arr, arrSize, &a, &b);
    printf("The pair with the highest product is %d and %d\n", a, b);

    return 0;
}
