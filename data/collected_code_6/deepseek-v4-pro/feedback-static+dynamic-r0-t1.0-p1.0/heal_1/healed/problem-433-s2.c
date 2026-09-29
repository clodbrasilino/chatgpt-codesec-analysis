#include <stdio.h>

int is_greater_than_all(int num, const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (num <= arr[i]) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int arr[] = {5, 10, 15, 20, 25};
    int size = sizeof(arr) / sizeof(arr[0]);
    int num;
    
    printf("Enter a number: ");
    scanf("%d", &num);
    
    if (is_greater_than_all(num, arr, size)) {
        printf("%d is greater than all elements in the array.\n", num);
    } else {
        printf("%d is not greater than all elements in the array.\n", num);
    }
    
    return 0;
}