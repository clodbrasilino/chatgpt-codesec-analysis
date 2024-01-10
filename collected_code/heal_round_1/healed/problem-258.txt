#include<stdio.h>

int countOddElements(const int arr[], const int size) {
    int count = 0;
 
    for(int i = 0; i < size; i++) {
        if(arr[i] % 2 != 0) {
            count++;
        }
    }
 
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Number of odd elements: %d\n", countOddElements(arr, size));
    return 0;
}