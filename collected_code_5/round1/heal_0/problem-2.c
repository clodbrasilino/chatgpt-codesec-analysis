#include <stdio.h>
#include <stdlib.h>

void find_similar_elements(int *arr1, int *arr2, int size1, int size2) {
    int i, j;
    for(i = 0; i<size1; i++) {
        for(j = 0; j<size2; j++) {
            if(arr1[i] == arr2[j]) {
                printf("%d ", arr1[i]);
                break;
            }
        }
    }
    printf("\n");
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 3, 4, 1, 7, 2};
    int size1 = sizeof(arr1)/sizeof(arr1[0]);
    int size2 = sizeof(arr2)/sizeof(arr2[0]);
    
    find_similar_elements(arr1, arr2, size1, size2);
    return 0;
}