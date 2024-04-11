#include <stdio.h>
#include <stdbool.h>

bool checkNumber(int num, int arr[], int size) {
    for(int i = 0; i < size; i++) {
        if(num <= arr[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if(checkNumber(num, arr, sizeof(arr)/sizeof(arr[0]))) {
        printf("The entered number is greater than all elements of the array.\n");
    } else {
        printf("The entered number is not greater than all elements of the array.\n");
    }
    return 0;
}