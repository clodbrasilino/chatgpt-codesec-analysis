#include <stdio.h>
#include <stdlib.h>

int min(int a, int b){
    return (a < b) ? a : b;  
} 

int minimumTotal(int** triangle, int triangleSize){
    int i, j;
    
    for(i = triangleSize - 2; i >= 0; i--){
        for(j = 0; j <= i; j++){
            triangle[i][j] += min(triangle[i+1][j], triangle[i+1][j+1]);
        }
    }
    return triangle[0][0];
}

int main() {
   int triangleSize = 4;
   int **triangle = malloc(triangleSize * sizeof(int *));
   for(int i = 0; i < triangleSize; i++){
       triangle[i] = malloc((i+1) * sizeof(int));
   }

   triangle[0][0] = 2;
   triangle[1][0] = 3;
   triangle[1][1] = 4;
   triangle[2][0] = 6;
   triangle[2][1] = 5;
   triangle[2][2] = 7;
   triangle[3][0] = 4;
   triangle[3][1] = 1;
   triangle[3][2] = 8;
   triangle[3][3] = 3;

   int minPathSum = minimumTotal(triangle, triangleSize);
   printf("Minimum total path sum is: %d\n", minPathSum);

   for(int i = 0; i < triangleSize; i++){
       free(triangle[i]);
   }
   
   free(triangle);

   return 0;
}