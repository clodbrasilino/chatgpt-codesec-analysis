#include <stdio.h>
#include <stdlib.h>

int oddSetBits(int *arr, int size) {
    int oddBitsCount = 0;
    for(int i = 0; i < size; i++) {
        int setBitsCount = 0;
        for(int j = 0; j < sizeof(int)*8; j++) {
            if(arr[i] & (1 << j)) {
                setBitsCount++;
            }
        }
        if(setBitsCount % 2 == 1) {
            oddBitsCount++;
        }
    }
    return oddBitsCount;
}

int main() {
    int size;
    scanf("%d", &size);
    int *arr = malloc(size * sizeof(int));
    if(arr == NULL) {
       printf("Memory allocation failed");
       exit(1);
    }

    for(int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    printf("%d",oddSetBits(arr, size));
    free(arr);
    return 0;
}