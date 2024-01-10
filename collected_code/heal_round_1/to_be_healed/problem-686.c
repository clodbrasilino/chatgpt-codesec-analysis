#include <stdio.h>

void find_frequency(int arr[], int size) {
    int count[size];
    
    for (int i = 0; i < size; i++) {
        count[i] = 0;
    }
    
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        count[arr[i]]++;
    }
    
    printf("Element  Frequency\n");
    
    for (int i = 0; i < size; i++) {
        if (count[i] != 0) {
            printf("%d         %d\n", i, count[i]);
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 2, 2, 4, 4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    find_frequency(arr, size);
    
    return 0;
}