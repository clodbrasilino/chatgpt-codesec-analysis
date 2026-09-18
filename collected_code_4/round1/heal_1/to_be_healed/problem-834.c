#include<stdio.h>
#include<stdlib.h>

void generateSpiralMatrix(int **matrix, int n){
    int count = 1;
    int rowStart = 0;
    int colStart = 0;
    int rowEnd = n-1;
    int colEnd = n-1;

    while (rowStart <= rowEnd && colStart <= colEnd){
        for(int i = colStart; i <= colEnd; i++){
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*matrix_75(D) + _2 + (long unsigned int)i * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             *  dereference of possibly-NULL 'matrix' [CWE-690] [-Wanalyzer-possible-null-dereference]
             *  use of uninitialized value '*matrix_75(D) + _2' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             */
            matrix[rowStart][i] = count;
            count++;
        }

        rowStart++;

        for(int i = rowStart; i <= rowEnd; i++){
            /* Possible weaknesses found:
             *  use of uninitialized value '*matrix_75(D) + _9' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             */
            matrix[i][colEnd] = count;
            count++;
        }

        colEnd--;

        if(rowStart <= rowEnd){
            for(int i = colEnd; i >= colStart; i--){
                matrix[rowEnd][i] = count;
                count++;
            }
        }
        rowEnd--;

        if(colStart<=colEnd){
            for(int i=rowEnd;i>=rowStart;i--){
                matrix[i][colStart]=count;
                count++;
            }
        }
        colStart++;
    }
    
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            /* Possible weaknesses found:
             *  use of uninitialized value '*_32 + _34' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             *  dereference of possibly-NULL '*matrix_75(D) + _30 + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;

    printf("Enter a number: ");
    scanf("%d",&n);

    int **matrix = (int**)malloc(n * sizeof(int *));
    for(int i=0; i<n; i++)
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'matrix' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        matrix[i] = (int*)malloc(n * sizeof(int));
        
    generateSpiralMatrix(matrix, n);
    
    for(int i=0; i<n; i++)
        free(matrix[i]);
        
    free(matrix);

    return 0;
}