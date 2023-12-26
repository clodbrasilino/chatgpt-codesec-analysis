#include <stdio.h>

#define N 5

void find_similar(int arr1[], int arr2[], int n) {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(arr1[i] == arr2[j]) {
                printf("%d ", arr1[i]);
                break;
            }
        }
    }
    printf("\n");
}

int main() {
    int arr1[N] = {1, 2, 3, 4, 5};
    int arr2[N] = {4, 5, 6, 7, 8};
    
    find_similar(arr1, arr2, N);

    return 0;
}