#include <stdio.h>
#include <stdlib.h>

void fill_magic_square(int **magic_square, const int size) {
    int i = 0, j = size / 2, num = 1;
    
    while (num <= size * size) {
        magic_square[i][j] = num++;
        
        i--;
        j++;
        
        if (i < 0 && j == size) {
            i += 2;
            j--;
        }
        else {
           if(j == size){
               j = 0;
           }
           else if(i < 0) {
               i = size - 1;
           }
        }  
    } 
}

void display_square(int **magic_square, const int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%4d ", magic_square[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int size;
    
    printf("Enter the size of magic square (odd number only): ");
    scanf("%d", &size);

    if(size < 0 || size % 2 == 0){
        printf("Size must be a positive odd number.\n");
        return 0;
    }

    int **magic_square = (int **)malloc(size * sizeof(int *));

    if (magic_square == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    for (int i = 0; i < size; ++i) {
        magic_square[i] = malloc(size * sizeof(int));

        if (magic_square[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 0;
        }
    }

    fill_magic_square(magic_square, size);
    
    display_square(magic_square, size);

    for(int i = 0; i < size; ++i)
        free(magic_square[i]);
    free(magic_square);

    return 0;
}