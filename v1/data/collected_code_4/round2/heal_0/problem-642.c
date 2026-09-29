#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROW 3 
#define COL 3 

bool areRowsSame(int M[ROW][COL], int row1, int row2) 
{ 
    for (int i=0; i<COL; i++) 
        if (M[row1][i] != M[row2][i]) 
            return false; 
    return true; 
} 
  
// Function to remove duplicate rows 
int removeDuplicateRows(int M[ROW][COL]) 
{ 
    int i, j, k;
 
    for (i=0; i<ROW; i++) 
    { 
        for (j=i+1; j<ROW; j++) 
        { 
            if (areRowsSame(M, i, j)) 
            { 
                for (k=j; k<ROW; k++) 
                {
                    int l;
                    for (l=0; l<COL; l++) 
                    {
                        M[k][l] = M[k+1][l]; 
                    }
                }
                ROW--; 
            } 
        } 
    } 
} 

void printRows(int M[ROW][COL]) 
{ 
    int i, j;
    for (i = 0; i < ROW; i++) 
    { 
        for (j = 0; j < COL; j++) 
            printf("%d ", M[i][j]); 
        printf("\n"); 
    } 
} 
  
int main() 
{ 
    int M[ROW][COL] = {{1, 6, 3}, {1, 2, 3}, {1, 2, 3}};
    printf("Before removing duplicates \n");
    printRows(M);
    removeDuplicateRows(M); 
    printf("After removing duplicates \n");
    printRows(M);
    return 0;
} 