#include <stdio.h>

void chunk_tuples(int *arr, int size, int n) {
    int i;
    for (i = 0; i < size; i += n) {
        int j;
        for (j = i; j < i + n; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("%d ", arr[j]);
        }
        printf("\n");
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int n = 3;
    
    chunk_tuples(arr, size, n);
    
    return 0;
}