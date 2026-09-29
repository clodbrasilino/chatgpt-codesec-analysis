#include<stdio.h>

#define M 3
#define N 4

void extract_even_elements(int arr[M][N]) {
    printf("Even elements: ");
    for(int i=0; i<M; i++) {
        for(int j=0; j<N; j++) {
            if(arr[i][j] % 2 == 0) {
                printf("%d ", arr[i][j]);
            }
        }
    }
    printf("\n");
}

int main() {
    int arr[M][N] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    extract_even_elements(arr);
    return 0;
}