#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int minNumToMakeEven(int* arr, int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }
    
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    
    if (sum % 2 == 0) {
        return 2;
    }
    return 1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int result = minNumToMakeEven(arr, size);
    
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Invalid input\n");
    }
    
    return 0;
}