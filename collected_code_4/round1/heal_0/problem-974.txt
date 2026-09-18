#include <stdio.h>
#include <stdlib.h>

#define N 3

int minimumTotal(int** triangle, int numRows) {
    int *total = malloc(sizeof(int) * numRows);
    total[0] = triangle[0][0];

    for(int i = 1; i < numRows; i++){
        total[i] = total[i - 1] + triangle[i][i];

        for(int j = i - 1; j > 0; j--){
            total[j] = triangle[i][j] + (total[j] < total[j - 1] ? total[j] : total[j - 1]);
        }

        total[0] += triangle[i][0];
    }

    int minTotal = total[0];

    for(int i = 1; i < numRows; i++){
        if(total[i] < minTotal){
            minTotal = total[i];
        }
    }

    free(total);
    
    return minTotal;
}

int main() {
    int numRows = N;
    int **triangle = malloc(sizeof(int*) * numRows);

    for(int i = 0; i < numRows; i++) {
        triangle[i] = malloc(sizeof(int) * (i + 1));

        for(int j = 0; j <= i; j++) {
            scanf("%d", &triangle[i][j]);
        }
    }

    int minTotal = minimumTotal(triangle, numRows);

    printf("The minimum total path sum in the triangle is: %d\n", minTotal);

    for(int i = 0; i < numRows; i++) {
        free(triangle[i]);
    }

    free(triangle);

    return 0;
}