#include <stdio.h>

void removeOddNumbers(int arr[], int size) {
    int temp[size];
    int j = 0;
    
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] % 2 == 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            temp[j] = arr[i];
            j++;
        }
    }
    
    printf("List without odd numbers: ");
    for (int i = 0; i < j; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'temp[i]' is initialized [premium-bughuntingUninit]
         */
        printf("%d ", temp[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    removeOddNumbers(arr, size);
    
    return 0;
}