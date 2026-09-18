#include <stdio.h>

#define ROWS 3
#define COLS 3

void printFirstElements(int *arr, int cols, int rows, int index)
{
    if(index<cols){
        for (int i = 0; i < rows; i++)
            printf("%d\n", *(arr + i*cols + index));
    }else{
        printf("Index out of range!\n");
    }
}

int main()
{
    int twoDArray[ROWS][COLS] = { { 1, 2, 3},
                                  { 4, 5, 6 },
                                  { 7, 8, 9 } };
    printFirstElements((int *)twoDArray, COLS, ROWS, 0);
    return 0;
}