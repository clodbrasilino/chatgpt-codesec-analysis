#include <stdio.h>

#define SIZE1 5
#define SIZE2 5

void findSimilar(int arr1[], int arr2[], int size1, int size2) {
    int i, j;
    
    for(i = 0; i < size1; ++i) {
        for(j = 0; j < size2; ++j) {
            if(arr1[i] == arr2[j]) {
                printf("%d ", arr1[i]);
                break;
            }
        }
    }
    printf("\n");
}

int main() {
    int arr1[SIZE1] = {1, 2, 3, 4, 5};
    int arr2[SIZE2] = {3, 4, 5, 6, 7};
    
    findSimilar(arr1, arr2, SIZE1, SIZE2);
    
    return 0;
}