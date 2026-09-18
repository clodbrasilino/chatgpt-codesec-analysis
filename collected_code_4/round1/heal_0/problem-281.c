#include <stdio.h>
#include <stdlib.h>

int areElementsUnique(int* arr, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            if(arr[i] == arr[j]) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    int size;
    printf("\nEnter the number of elements : ");
    scanf("%d",&size);

    int* arr = (int*)malloc(size * sizeof(int));
    if(arr == NULL) {
        printf("Memory allocation unsuccessful");
        return 1;
    }

    printf("\nEnter elements : ");
    for(int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    if(areElementsUnique(arr, size)) {
        printf("\nElements are unique");
    } else {
        printf("\nElements are not unique");
    }

    free(arr);
    return 0;
}