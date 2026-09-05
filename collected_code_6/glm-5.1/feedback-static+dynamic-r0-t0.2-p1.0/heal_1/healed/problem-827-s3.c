#include <stdio.h>
#include <stdlib.h>

int sum_column(int * const *lists, const int *sizes, int num_lists, int col) {
    int total = 0;
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] != NULL && col >= 0 && col < sizes[i]) {
            total += lists[i][col];
        }
    }
    return total;
}

int main(void) {
    int row0[] = {1, 2, 3};
    int row1[] = {4, 5};
    int row2[] = {7, 8, 9, 10};
    
    int *lists[] = {row0, row1, row2};
    int sizes[] = {3, 2, 4};
    int num_lists = 3;
    int col = 1;
    
    int result = sum_column(lists, sizes, num_lists, col);
    printf("%d\n", result);
    
    return 0;
}