#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int findMaxTotal(int **triangle, int n) {
    if(triangle == NULL){
        return -1;
    }
    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            triangle[i][j] += MAX(triangle[i + 1][j], triangle[i + 1][j + 1]);
        }
    }
    return triangle[0][0];
}

int main() {
    int n;
    if(scanf("%d", &n)!=1){
        return -1;
    }
    int **triangle = (int **)malloc(n * sizeof(int *));
    if(triangle == NULL){
        return -1;
    }
    for (int i = 0; i < n; ++i) {
        triangle[i] = (int *)malloc((i + 1) * sizeof(int));
        if(triangle[i] == NULL){
            for(int j=0; j<i; j++){
                free(triangle[j]);
            }
            free(triangle);
            return -1;
        }
        for (int j = 0; j <= i; ++j) {
            if(scanf("%d", &triangle[i][j])!=1){
                for(int k=0; k<=i; k++){
                    free(triangle[k]);
                }
                free(triangle);
                return -1;
            }
        }
    }
    printf("%d\n", findMaxTotal(triangle, n));
    for (int i = 0; i < n; ++i) {
        free(triangle[i]);
    }
    free(triangle);
    return 0;
}