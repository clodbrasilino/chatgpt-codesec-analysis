#include <stdio.h>
#include <stdbool.h>

bool is_greater_than_all(int num, const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        if (num <= arr[i]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int arr[] = {1, 5, 8, 12, 20};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int num;

    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (is_greater_than_all(num, arr, size)) {
        printf("The number %d is greater than all elements in the array.\n", num);
    } else {
        printf("The number %d is not greater than all elements in the array.\n", num);
    }

    return 0;
}