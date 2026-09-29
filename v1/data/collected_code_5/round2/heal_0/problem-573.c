#include <stdio.h>

int product_of_unique(int arr[], int length) {
    int product = 1;
    for(int i = 0; i < length; i++) {
        int j;
        for(j = 0; j < i; j++)
           if(arr[i] == arr[j])
              break;
        if(i == j)
           product *= arr[i];
    }
    return product;
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 2, 3, 1};
    int len = sizeof(array) / sizeof(array[0]);
    printf("The product of unique numbers is: %d\n", product_of_unique(array, len));
    return 0;
}