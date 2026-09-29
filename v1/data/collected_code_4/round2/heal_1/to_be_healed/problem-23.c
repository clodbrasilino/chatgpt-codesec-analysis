#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

int maxSubArraySum(int *a, int size) {
   int max_so_far = a[0];
   int curr_max = a[0];

   for (int i = 1; i < size; i++) {
      curr_max = max(a[i], curr_max+a[i]);
      max_so_far = max(max_so_far, curr_max);
   }
   return max_so_far;
}

int maxSumListofLists(int **a, int rows, int cols){
    int maxSum = 0;
    for(int i=0; i<rows; i++){
        maxSum =  max(maxSum, maxSubArraySum(a[i], cols));
    }
    return maxSum;
}

int main() {
    int rows, cols;
    scanf("%d %d", &rows, &cols);
    int **arr = (int **)malloc(rows * sizeof(int *));
    for(int i=0; i<rows; i++){
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'arr' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        arr[i] = (int *)malloc(cols * sizeof(int));
    }

    for (int i=0; i<rows; i++)
        for (int j=0; j<cols; j++)
            scanf("%d", &arr[i][j]);

    int result = maxSumListofLists(arr, rows, cols);
    printf("%d", result);

    for(int i=0; i<rows; i++){
        free(arr[i]);
    }
    free(arr);
    return 0;
}