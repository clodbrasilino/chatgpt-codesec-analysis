#include <stdio.h>

void removeElements(int arr[], int n, int dataType) {
    int index = 0;
    int i;
  
    for (i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] != dataType) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            arr[index++] = arr[i];
        }
    }
  
    while (index < n) {
        arr[index++] = 0;
    }
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5, 6};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    int dataType = 4;
  
    printf("Original Tuple:\n");
    for (int i = 0; i < size; i++) {
        printf("%d\n", tuple[i]);
    }
  
    removeElements(tuple, size, dataType);
  
    printf("\nTuple after removing %d:\n", dataType);
    for (int i = 0; i < size; i++) {
        printf("%d\n", tuple[i]);
    }
  
    return 0;
}