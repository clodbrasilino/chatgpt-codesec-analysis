#include <stdio.h>

int isLastElementEven(int arr[], int size, int p) {
    if(size == 0) {
        return -1;
    }
    
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[size-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int lastElement = arr[size-1];
    for(int i = 0; i < p; i++) {
        lastElement = lastElement * lastElement;
    }
    
    return (lastElement % 2 == 0) ? 1 : 0;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int p = 3;
    
    int result = isLastElementEven(arr, size, p);
    
    if(result == 1) {
        printf("Last element is even\n");
    } else if(result == 0) {
        printf("Last element is odd\n");
    } else {
        printf("Array is empty\n");
    }
    
    return 0;
}