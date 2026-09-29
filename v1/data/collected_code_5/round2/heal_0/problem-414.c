#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool check_value(int* arr, int len, int val) {
    for(int i = 0; i < len; i++) {
        if(arr[i] == val)
            return true;
    }

    return false;
}

int main() {
    int len, val;
    
    printf("Enter the number of elements in the array: ");
    scanf("%d", &len);

    int* arr = (int*) malloc(len * sizeof(int));
    if(arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter the elements of the array: ");
    for(int i = 0; i < len; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the value to check for: ");
    scanf("%d", &val);

    bool result = check_value(arr, len, val);

    if(result)
        printf("Value found\n");
    else
        printf("Value not found\n");

    free(arr);
    return 0;
}