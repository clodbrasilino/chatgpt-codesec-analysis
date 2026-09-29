#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ROW 3 
#define MAX_COL 3 

bool areRowsSame(int M[MAX_ROW][MAX_COL], int row1, int row2, int COL) 
{ 
    for (int i=0; i<COL; i++) 
        if (M[row1][i] != M[row2][i]) 
            return false; 
    return true; 
} 

int removeDuplicateRows(int M[MAX_ROW][MAX_COL], int ROW, int COL) 
{ 
    int i, j, k;

    for (i=0; i<ROW; i++) 
    { 
        for (j=i+1; j<ROW; j++) 
        { 
            if (areRowsSame(M, i, j, COL)) 
            { 
                for (k=j; k<ROW-1; k++) 
                {
                    for (int l=0; l<COL; l++) 
                    {
                        M[k][l] = M[k+1][l]; 
                    }
                }
                ROW--; 
                j--;
            } 
        } 
    }
  
    return ROW;
} 

void printRows(int M[MAX_ROW][MAX_COL], int ROW, int COL) 
{ 
    for (int i = 0; i < ROW; i++) 
    { 
        for (int j = 0; j < COL; j++) 
            printf("%d ", M[i][j]); 
        printf("\n"); 
    } 
} 
  
int main() 
{ 
    int M[MAX_ROW][MAX_COL] = {{1, 6, 3}, {1, 2, 3}, {1, 2, 3}};
    int ROW = MAX_ROW;
    int COL = MAX_COL;
    printf("Before removing duplicates \n");
    printRows(M, ROW, COL);
    ROW = removeDuplicateRows(M, ROW, COL); 
    printf("After removing duplicates \n");
    printRows(M, ROW, COL);
    return 0;
}